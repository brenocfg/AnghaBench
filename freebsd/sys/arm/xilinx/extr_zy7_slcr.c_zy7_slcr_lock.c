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
struct zy7_slcr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WR4 (struct zy7_slcr_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZY7_SLCR_LOCK ; 
 int /*<<< orphan*/  ZY7_SLCR_LOCK_MAGIC ; 

__attribute__((used)) static void
zy7_slcr_lock(struct zy7_slcr_softc *sc)
{

	/* Lock SLCR with magic number. */
	WR4(sc, ZY7_SLCR_LOCK, ZY7_SLCR_LOCK_MAGIC);
}