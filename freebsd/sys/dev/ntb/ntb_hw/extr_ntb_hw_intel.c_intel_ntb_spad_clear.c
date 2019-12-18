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
struct ntb_softc {unsigned int spad_count; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_spad_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_ntb_spad_clear(device_t dev)
{
	struct ntb_softc *ntb = device_get_softc(dev);
	unsigned i;

	for (i = 0; i < ntb->spad_count; i++)
		intel_ntb_spad_write(dev, i, 0);
}