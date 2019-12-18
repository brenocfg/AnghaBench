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
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  cp_handle_interrupt (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_interrupt_poll (int /*<<< orphan*/ *,int) ; 

int cp_interrupt(s*b){int l215=0;{l276:if(!(
cp_interrupt_poll(b,1)!=0))goto l269;{{if(!(++l215>1000))goto l242;
return-1;l242:;}cp_handle_interrupt(b);}goto l276;l269:;}return l215;
}