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
struct rk_strpool {int dummy; } ;
struct TYPE_3__ {size_t length; char* components; } ;
typedef  TYPE_1__ heim_oid ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 char* rk_strpoolcollect (struct rk_strpool*) ; 
 struct rk_strpool* rk_strpoolprintf (struct rk_strpool*,char*,char) ; 

int
der_print_heim_oid (const heim_oid *oid, char delim, char **str)
{
    struct rk_strpool *p = NULL;
    size_t i;

    if (oid->length == 0)
	return EINVAL;

    for (i = 0; i < oid->length ; i++) {
	p = rk_strpoolprintf(p, "%d", oid->components[i]);
	if (p && i < oid->length - 1)
	    p = rk_strpoolprintf(p, "%c", delim);
	if (p == NULL) {
	    *str = NULL;
	    return ENOMEM;
	}
    }

    *str = rk_strpoolcollect(p);
    if (*str == NULL)
	return ENOMEM;
    return 0;
}