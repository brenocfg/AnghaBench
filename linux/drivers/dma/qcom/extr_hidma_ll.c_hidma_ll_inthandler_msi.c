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
struct hidma_lldev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  hidma_ll_int_handler_internal (struct hidma_lldev*,int) ; 

irqreturn_t hidma_ll_inthandler_msi(int chirq, void *arg, int cause)
{
	struct hidma_lldev *lldev = arg;

	hidma_ll_int_handler_internal(lldev, cause);
	return IRQ_HANDLED;
}