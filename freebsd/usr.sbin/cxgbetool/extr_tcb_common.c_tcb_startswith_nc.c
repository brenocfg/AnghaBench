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

/* Variables and functions */
 scalar_t__ strlen (char*) ; 
 scalar_t__ tcb_strncmp_nc (char*,char*,int) ; 

int
tcb_startswith_nc(char *cs, char *ct)
{ /* return true if cs start with ct */
    return (0 == tcb_strncmp_nc(cs, ct, (int)strlen(ct)));
}