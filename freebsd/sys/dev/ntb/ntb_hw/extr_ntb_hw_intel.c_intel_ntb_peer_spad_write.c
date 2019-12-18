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
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_softc {unsigned int spad_count; TYPE_1__* peer_reg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ spad; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTB_SDOORBELL_LOCKUP ; 
 scalar_t__ XEON_SPAD_OFFSET ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_mw_write (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_reg_write (int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_ntb_peer_spad_write(device_t dev, unsigned int idx, uint32_t val)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	if (idx >= ntb->spad_count)
		return (EINVAL);

	if (HAS_FEATURE(ntb, NTB_SDOORBELL_LOCKUP))
		intel_ntb_mw_write(4, XEON_SPAD_OFFSET + idx * 4, val);
	else
		intel_ntb_reg_write(4, ntb->peer_reg->spad + idx * 4, val);

	return (0);
}