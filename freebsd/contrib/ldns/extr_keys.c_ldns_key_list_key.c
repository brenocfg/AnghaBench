#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** _keys; } ;
typedef  TYPE_1__ ldns_key_list ;
typedef  int /*<<< orphan*/  ldns_key ;

/* Variables and functions */
 size_t ldns_key_list_key_count (TYPE_1__ const*) ; 

ldns_key *
ldns_key_list_key(const ldns_key_list *key, size_t nr)
{       
	if (nr < ldns_key_list_key_count(key)) {
		return key->_keys[nr];
	} else {
		return NULL;
	}
}