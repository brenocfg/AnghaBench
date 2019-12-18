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
struct ida_softc {int dummy; } ;
struct ida_qcb {int /*<<< orphan*/  hwqcb_busaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_42XX_REQUEST ; 
 int /*<<< orphan*/  ida_outl (struct ida_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ida_v4_submit(struct ida_softc *ida, struct ida_qcb *qcb)
{
	ida_outl(ida, R_42XX_REQUEST, qcb->hwqcb_busaddr);
}