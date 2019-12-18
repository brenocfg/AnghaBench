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
typedef  int /*<<< orphan*/  ldns_key_list ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_key_list_key (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_key_list_key_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_key_set_use (int /*<<< orphan*/ ,int) ; 

void
ldns_key_list_set_use(ldns_key_list *keys, bool v)
{
	size_t i;

	for (i = 0; i < ldns_key_list_key_count(keys); i++) {
		ldns_key_set_use(ldns_key_list_key(keys, i), v);
	}
}