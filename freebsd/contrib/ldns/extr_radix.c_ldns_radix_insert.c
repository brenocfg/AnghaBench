#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int radix_strlen_t ;
typedef  int /*<<< orphan*/  ldns_status ;
struct TYPE_12__ {int /*<<< orphan*/  count; TYPE_2__* root; } ;
typedef  TYPE_1__ ldns_radix_t ;
struct TYPE_13__ {scalar_t__ len; scalar_t__* key; int klen; scalar_t__ offset; struct TYPE_13__* array; struct TYPE_13__* edge; scalar_t__ parent_index; struct TYPE_13__* parent; void* data; int /*<<< orphan*/  str; } ;
typedef  TYPE_2__ ldns_radix_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  LDNS_STATUS_EXISTS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_NULL ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ldns_radix_array_space (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_radix_array_split (TYPE_2__*,scalar_t__*,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_radix_find_prefix (TYPE_1__*,scalar_t__*,int,TYPE_2__**,int*) ; 
 TYPE_2__* ldns_radix_new_node (void*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ldns_radix_prefix_remainder (int,scalar_t__*,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  ldns_radix_str_create (TYPE_2__*,scalar_t__*,int,int) ; 

ldns_status
ldns_radix_insert(ldns_radix_t* tree, uint8_t* key, radix_strlen_t len,
	void* data)
{
	radix_strlen_t pos = 0;
	ldns_radix_node_t* add = NULL;
	ldns_radix_node_t* prefix = NULL;

	if (!tree || !key || !data) {
		return LDNS_STATUS_NULL;
	}
	add = ldns_radix_new_node(data, key, len);
	if (!add) {
		return LDNS_STATUS_MEM_ERR;
	}
	/** Search the trie until we can make no further process. */
	if (!ldns_radix_find_prefix(tree, key, len, &prefix, &pos)) {
		/** No prefix found */
		assert(tree->root == NULL);
		if (len == 0) {
			/**
			 * Example 1: The root:
			 * | [0]
			 **/
			tree->root = add;
		} else {
			/** Example 2: 'dns':
			 * | [0]
			 * --| [d+ns] dns
			 **/
			prefix = ldns_radix_new_node(NULL, (uint8_t*)"", 0);
			if (!prefix) {
				LDNS_FREE(add);
				return LDNS_STATUS_MEM_ERR;
			}
			/** Find some space in the array for the first byte */
			if (!ldns_radix_array_space(prefix, key[0])) {
				LDNS_FREE(add);
				LDNS_FREE(prefix->array);
				LDNS_FREE(prefix);
				return LDNS_STATUS_MEM_ERR;
			}
			/** Set relational pointers */
			add->parent = prefix;
			add->parent_index = 0;
			prefix->array[0].edge = add;
			if (len > 1) {
				/** Store the remainder of the prefix */
				if (!ldns_radix_prefix_remainder(1, key,
					len, &prefix->array[0].str,
					&prefix->array[0].len)) {
					LDNS_FREE(add);
					LDNS_FREE(prefix->array);
					LDNS_FREE(prefix);
					return LDNS_STATUS_MEM_ERR;
				}
			}
			tree->root = prefix;
		}
	} else if (pos == len) {
		/** Exact match found */
		if (prefix->data) {
			/* Element already exists */
			LDNS_FREE(add);
			return LDNS_STATUS_EXISTS_ERR;
		}
		prefix->data = data;
		prefix->key = key;
		prefix->klen = len; /* redundant */
	} else {
		/** Prefix found */
		uint8_t byte = key[pos];
		assert(pos < len);
		if (byte < prefix->offset ||
			(byte - prefix->offset) >= prefix->len) {
			/** Find some space in the array for the byte. */
			/**
			 * Example 3: 'ldns'
			 * | [0]
			 * --| [d+ns] dns
			 * --| [l+dns] ldns
			 **/
			if (!ldns_radix_array_space(prefix, byte)) {
				LDNS_FREE(add);
				return LDNS_STATUS_MEM_ERR;
			}
			assert(byte >= prefix->offset);
			assert((byte - prefix->offset) <= prefix->len);
			byte -= prefix->offset;
			if (pos+1 < len) {
				/** Create remainder of the string. */
				if (!ldns_radix_str_create(
					&prefix->array[byte], key, pos+1,
					len)) {
					LDNS_FREE(add);
					return LDNS_STATUS_MEM_ERR;
				}
			}
			/** Add new node. */
			add->parent = prefix;
			add->parent_index = byte;
			prefix->array[byte].edge = add;
		} else if (prefix->array[byte-prefix->offset].edge == NULL) {
			/** Use existing element. */
			/**
			 * Example 4: 'edns'
			 * | [0]
			 * --| [d+ns] dns
			 * --| [e+dns] edns
			 * --| [l+dns] ldns
			 **/
			byte -= prefix->offset;
			if (pos+1 < len) {
				/** Create remainder of the string. */
				if (!ldns_radix_str_create(
					&prefix->array[byte], key, pos+1,
					len)) {
					LDNS_FREE(add);
					return LDNS_STATUS_MEM_ERR;
				}
			}
			/** Add new node. */
			add->parent = prefix;
			add->parent_index = byte;
			prefix->array[byte].edge = add;
		} else {
			/**
			 * Use existing element, but it has a shared prefix,
			 * we need a split.
			 */
			if (!ldns_radix_array_split(&prefix->array[byte-(prefix->offset)],
				key, pos+1, len, add)) {
				LDNS_FREE(add);
				return LDNS_STATUS_MEM_ERR;
			}
		}
	}

	tree->count ++;
	return LDNS_STATUS_OK;
}