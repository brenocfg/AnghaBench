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
typedef  int /*<<< orphan*/ * heim_general_string ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ * const) ; 

int
der_copy_general_string (const heim_general_string *from,
			 heim_general_string *to)
{
    *to = strdup(*from);
    if(*to == NULL)
	return ENOMEM;
    return 0;
}