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
struct keys_array {int dummy; } ;
struct key_value {struct bwstring* k; } ;
struct bwstring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwsfree (struct bwstring*) ; 
 struct key_value* get_key_from_keys_array (struct keys_array*,size_t) ; 
 size_t keys_num ; 

void
set_key_on_keys_array(struct keys_array *ka, struct bwstring *s, size_t ind)
{

	if (ka && keys_num > ind) {
		struct key_value *kv;

		kv = get_key_from_keys_array(ka, ind);

		if (kv->k && kv->k != s)
			bwsfree(kv->k);
		kv->k = s;
	}
}