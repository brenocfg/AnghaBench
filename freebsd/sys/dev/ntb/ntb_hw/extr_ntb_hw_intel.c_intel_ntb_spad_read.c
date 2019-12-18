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
struct ntb_softc {unsigned int spad_count; TYPE_1__* self_reg; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ spad; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_reg_read (int,scalar_t__) ; 

__attribute__((used)) static int
intel_ntb_spad_read(device_t dev, unsigned int idx, uint32_t *val)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	if (idx >= ntb->spad_count)
		return (EINVAL);

	*val = intel_ntb_reg_read(4, ntb->self_reg->spad + idx * 4);

	return (0);
}