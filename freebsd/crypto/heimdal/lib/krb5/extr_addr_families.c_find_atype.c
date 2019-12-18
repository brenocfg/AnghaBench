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
struct addr_operations {scalar_t__ atype; } ;
typedef  scalar_t__ krb5_address_type ;

/* Variables and functions */
 struct addr_operations* at ; 
 int num_addrs ; 

__attribute__((used)) static struct addr_operations *
find_atype(krb5_address_type atype)
{
    struct addr_operations *a;

    for (a = at; a < at + num_addrs; ++a)
	if (atype == a->atype)
	    return a;
    return NULL;
}