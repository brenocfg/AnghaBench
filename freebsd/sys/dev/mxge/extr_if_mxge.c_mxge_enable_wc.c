#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_3__ {int wc; int /*<<< orphan*/  dev; scalar_t__ sram; int /*<<< orphan*/  mem_res; } ;
typedef  TYPE_1__ mxge_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAT_WRITE_COMBINING ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pmap_change_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mxge_enable_wc(mxge_softc_t *sc)
{
#if defined(__i386) || defined(__amd64)
	vm_offset_t len;
	int err;

	sc->wc = 1;
	len = rman_get_size(sc->mem_res);
	err = pmap_change_attr((vm_offset_t) sc->sram,
			       len, PAT_WRITE_COMBINING);
	if (err != 0) {
		device_printf(sc->dev, "pmap_change_attr failed, %d\n",
			      err);
		sc->wc = 0;
	}
#endif		
}