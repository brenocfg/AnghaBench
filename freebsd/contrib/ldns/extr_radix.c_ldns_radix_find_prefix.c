#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t radix_strlen_t ;
struct TYPE_7__ {TYPE_3__* root; } ;
typedef  TYPE_2__ ldns_radix_t ;
struct TYPE_8__ {size_t offset; size_t len; TYPE_1__* array; } ;
typedef  TYPE_3__ ldns_radix_node_t ;
struct TYPE_6__ {scalar_t__ len; TYPE_3__* edge; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ memcmp (size_t*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
ldns_radix_find_prefix(ldns_radix_t* tree, uint8_t* key,
	radix_strlen_t len, ldns_radix_node_t** result, radix_strlen_t* respos)
{
	/** Start searching at the root node */
	ldns_radix_node_t* n = tree->root;
	radix_strlen_t pos = 0;
	uint8_t byte;
	*respos = 0;
	*result = n;
        if (!n) {
		/** No root, no prefix found */
		return 0;
	}
	/** For each node, look if we can make further progress */
	while (n) {
		if (pos == len) {
			/** Exact match */
			return 1;
		}
		byte = key[pos];
		if (byte < n->offset) {
			/** key < node */
			return 1;
		}
		byte -= n->offset;
		if (byte >= n->len) {
			/** key > node */
			return 1;
		}
		/** So far, the trie matches */
		pos++;
		if (n->array[byte].len != 0) {
			/** Must match additional string */
			if (pos + n->array[byte].len > len) {
				return 1; /* no match at child node */
			}
			if (memcmp(&key[pos], n->array[byte].str,
				n->array[byte].len) != 0) {
				return 1; /* no match at child node */
			}
			pos += n->array[byte].len;
		}
		/** Continue searching prefix at this child node */
		n = n->array[byte].edge;
		if (!n) {
			return 1;
		}
		/** Update the prefix node */
		*respos = pos;
		*result = n;
	}
	/** Done */
	return 1;
}