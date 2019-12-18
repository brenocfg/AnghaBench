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
struct ostm_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ OSTM_TE ; 
 scalar_t__ OSTM_TT ; 
 int TE ; 
 int /*<<< orphan*/  TT ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ostm_timer_stop(struct ostm_device *ostm)
{
	if (readb(ostm->base + OSTM_TE) & TE) {
		writeb(TT, ostm->base + OSTM_TT);

		/*
		 * Read back the register simply to confirm the write operation
		 * has completed since I/O writes can sometimes get queued by
		 * the bus architecture.
		 */
		while (readb(ostm->base + OSTM_TE) & TE)
			;
	}
}