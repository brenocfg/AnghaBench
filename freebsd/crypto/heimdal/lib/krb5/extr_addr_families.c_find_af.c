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
struct addr_operations {int af; } ;

/* Variables and functions */
 struct addr_operations* at ; 
 int num_addrs ; 

__attribute__((used)) static struct addr_operations *
find_af(int af)
{
    struct addr_operations *a;

    for (a = at; a < at + num_addrs; ++a)
	if (af == a->af)
	    return a;
    return NULL;
}