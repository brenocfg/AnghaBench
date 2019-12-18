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
typedef  int /*<<< orphan*/  u_char ;
struct viapm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_VAL ; 
 int /*<<< orphan*/  VIAPM_INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_LOCK (struct viapm_softc*) ; 
 int /*<<< orphan*/  VIAPM_OUTB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_SDA ; 
 int /*<<< orphan*/  VIAPM_UNLOCK (struct viapm_softc*) ; 
 struct viapm_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
viabb_setsda(device_t dev, int data)
{
	struct viapm_softc *viapm = device_get_softc(dev);
	u_char val;

	VIAPM_LOCK(viapm);
	val = VIAPM_INB(GPIO_VAL);

	if (data)
		val |= VIAPM_SDA;
	else
		val &= ~VIAPM_SDA;

	VIAPM_OUTB(GPIO_VAL, val);
	VIAPM_UNLOCK(viapm);

	return;
}