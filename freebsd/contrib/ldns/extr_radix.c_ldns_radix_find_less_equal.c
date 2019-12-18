#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t radix_strlen_t ;
struct TYPE_15__ {TYPE_3__* root; } ;
typedef  TYPE_2__ ldns_radix_t ;
struct TYPE_16__ {size_t offset; size_t len; scalar_t__ data; TYPE_1__* array; } ;
typedef  TYPE_3__ ldns_radix_node_t ;
struct TYPE_14__ {scalar_t__ len; TYPE_3__* edge; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 TYPE_3__* ldns_radix_last_in_subtree_incl_self (TYPE_3__*) ; 
 TYPE_3__* ldns_radix_prev (TYPE_3__*) ; 
 TYPE_3__* ldns_radix_prev_from_index (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ldns_radix_self_or_prev (TYPE_3__*,TYPE_3__**) ; 
 int memcmp (size_t const*,int /*<<< orphan*/ ,size_t) ; 

int
ldns_radix_find_less_equal(ldns_radix_t* tree, const uint8_t* key,
	radix_strlen_t len, ldns_radix_node_t** result)
{
	ldns_radix_node_t* node = NULL;
	radix_strlen_t pos = 0;
	uint8_t byte;
	int memcmp_res = 0;

	if (!tree || !tree->root || !key) {
		*result = NULL;
		return 0;
	}

	node = tree->root;
	while (pos < len) {
		byte = key[pos];
		if (byte < node->offset) {
			/**
			 * No exact match. The lesser is in this or the
			 * previous node.
			 */
			ldns_radix_self_or_prev(node, result);
			return 0;
		}
		byte -= node->offset;
		if (byte >= node->len) {
			/**
			 * No exact match. The lesser is in this node or the
			 * last of this array, or something before this node.
			 */
			*result = ldns_radix_last_in_subtree_incl_self(node);
			if (*result == NULL) {
				*result = ldns_radix_prev(node);
			}
			return 0;
		}
		pos++;
		if (!node->array[byte].edge) {
			/**
			 * No exact match. Find the previous in the array
			 * from this index.
			 */
			*result = ldns_radix_prev_from_index(node, byte);
			if (*result == NULL) {
				ldns_radix_self_or_prev(node, result);
			}
			return 0;
		}
		if (node->array[byte].len != 0) {
			/** Must match additional string. */
			if (pos + node->array[byte].len > len) {
				/** Additional string is longer than key. */
				if (memcmp(&key[pos], node->array[byte].str,
					len-pos) <= 0) {
					/** Key is before this node. */
					*result = ldns_radix_prev(
						node->array[byte].edge);
				} else {
					/** Key is after additional string. */
					*result = ldns_radix_last_in_subtree_incl_self(node->array[byte].edge);
					if (*result == NULL) {
						 *result = ldns_radix_prev(node->array[byte].edge);
					}
				}
				return 0;
			}
			memcmp_res = memcmp(&key[pos], node->array[byte].str,
				node->array[byte].len);
			if (memcmp_res < 0) {
				*result = ldns_radix_prev(
					node->array[byte].edge);
				return 0;
			} else if (memcmp_res > 0) {
				*result = ldns_radix_last_in_subtree_incl_self(node->array[byte].edge);
				if (*result == NULL) {
					 *result = ldns_radix_prev(node->array[byte].edge);
				}
				return 0;
			}

			pos += node->array[byte].len;
		}
		node = node->array[byte].edge;
	}
	if (node->data) {
		/** Exact match. */
		*result = node;
		return 1;
	}
	/** There is a node which is an exact match, but has no element. */
	*result = ldns_radix_prev(node);
	return 0;
}