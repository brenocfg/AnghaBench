#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sort_list_item {scalar_t__ str; int /*<<< orphan*/  ka; } ;
struct key_value {scalar_t__ k; } ;

/* Variables and functions */
 scalar_t__ bws_memsize (scalar_t__) ; 
 struct key_value* get_key_from_keys_array (int /*<<< orphan*/ *,size_t) ; 
 int keys_array_size () ; 
 size_t keys_num ; 

size_t
sort_list_item_size(struct sort_list_item *si)
{
	size_t ret = 0;

	if (si) {
		ret = sizeof(struct sort_list_item) + keys_array_size();
		if (si->str)
			ret += bws_memsize(si->str);
		for (size_t i = 0; i < keys_num; ++i) {
			const struct key_value *kv;

			kv = get_key_from_keys_array(&si->ka, i);

			if (kv->k != si->str)
				ret += bws_memsize(kv->k);
		}
	}
	return (ret);
}