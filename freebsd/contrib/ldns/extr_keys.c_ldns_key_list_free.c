#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* _keys; } ;
typedef  TYPE_1__ ldns_key_list ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_key_deep_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_key_list_key (TYPE_1__*,size_t) ; 
 size_t ldns_key_list_key_count (TYPE_1__*) ; 

void
ldns_key_list_free(ldns_key_list *key_list)
{
	size_t i;
	for (i = 0; i < ldns_key_list_key_count(key_list); i++) {
		ldns_key_deep_free(ldns_key_list_key(key_list, i));
	}
	LDNS_FREE(key_list->_keys);
	LDNS_FREE(key_list);
}