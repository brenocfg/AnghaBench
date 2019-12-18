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
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

size_t
strlenout(vm_offset_t src)
{
    char	c;
    size_t	len;
    
    for (len = 0; ; len++) {
	archsw.arch_copyout(src++, &c, 1);
	if (c == 0)
	    break;
    }
    return(len);
}