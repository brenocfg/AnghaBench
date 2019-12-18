#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t _key_count; } ;
typedef  TYPE_1__ ldns_key_list ;

/* Variables and functions */

void            
ldns_key_list_set_key_count(ldns_key_list *key, size_t count)
{
	        key->_key_count = count;
}