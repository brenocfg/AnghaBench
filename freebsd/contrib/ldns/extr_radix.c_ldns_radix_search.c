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
struct TYPE_8__ {size_t offset; size_t len; TYPE_1__* array; scalar_t__ data; } ;
typedef  TYPE_3__ ldns_radix_node_t ;
struct TYPE_6__ {scalar_t__ len; TYPE_3__* edge; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ memcmp (size_t const*,int /*<<< orphan*/ ,size_t) ; 

ldns_radix_node_t*
ldns_radix_search(ldns_radix_t* tree, const uint8_t* key, radix_strlen_t len)
{
	ldns_radix_node_t* node = NULL;
	radix_strlen_t pos = 0;
	uint8_t byte = 0;

	if (!tree || !key) {
		return NULL;
	}
	node = tree->root;
	while (node) {
		if (pos == len) {
			return node->data?node:NULL;
		}
		byte = key[pos];
		if (byte < node->offset) {
			return NULL;
		}
		byte -= node->offset;
		if (byte >= node->len) {
			return NULL;
		}
		pos++;
		if (node->array[byte].len > 0) {
			/** Must match additional string. */
			if (pos + node->array[byte].len > len) {
				return NULL;
			}
			if (memcmp(&key[pos], node->array[byte].str,
				node->array[byte].len) != 0) {
				return NULL;
			}
			pos += node->array[byte].len;
		}
		node = node->array[byte].edge;
	}
	return NULL;
}