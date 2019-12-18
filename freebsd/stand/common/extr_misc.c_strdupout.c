#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* arch_copyout ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 TYPE_1__ archsw ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ strlenout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

char *
strdupout(vm_offset_t str)
{
    char	*result, *cp;
    
    result = malloc(strlenout(str) + 1);
    for (cp = result; ;cp++) {
	archsw.arch_copyout(str++, cp, 1);
	if (*cp == 0)
	    break;
    }
    return(result);
}