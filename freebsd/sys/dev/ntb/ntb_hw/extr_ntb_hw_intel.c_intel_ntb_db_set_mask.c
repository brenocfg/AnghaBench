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
typedef  int /*<<< orphan*/  uint64_t ;
struct ntb_softc {int /*<<< orphan*/  db_mask; TYPE_1__* self_reg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  db_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_MASK_LOCK (struct ntb_softc*) ; 
 int /*<<< orphan*/  DB_MASK_UNLOCK (struct ntb_softc*) ; 
 int /*<<< orphan*/  HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 int /*<<< orphan*/  db_iowrite (struct ntb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_ntb_db_set_mask(device_t dev, uint64_t bits)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	DB_MASK_LOCK(ntb);
	ntb->db_mask |= bits;
	if (!HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP))
		db_iowrite(ntb, ntb->self_reg->db_mask, ntb->db_mask);
	DB_MASK_UNLOCK(ntb);
}