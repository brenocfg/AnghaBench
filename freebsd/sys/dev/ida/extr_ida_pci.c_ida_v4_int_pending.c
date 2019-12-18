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

/* Variables and functions */
 int /*<<< orphan*/  R_42XX_STATUS ; 
 int STATUS_42XX_INT_PENDING ; 
 int ida_inl (struct ida_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ida_v4_int_pending(struct ida_softc *ida)
{
	return (ida_inl(ida, R_42XX_STATUS) & STATUS_42XX_INT_PENDING);
}