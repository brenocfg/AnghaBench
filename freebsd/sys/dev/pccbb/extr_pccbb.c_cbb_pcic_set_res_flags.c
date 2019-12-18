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
typedef  int /*<<< orphan*/  u_long ;
struct resource {int dummy; } ;
struct cbb_softc {int /*<<< orphan*/ * exca; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int SYS_RES_MEMORY ; 
 struct resource* cbb_find_res (struct cbb_softc*,int,int) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int exca_mem_set_flags (int /*<<< orphan*/ *,struct resource*,int /*<<< orphan*/ ) ; 

int
cbb_pcic_set_res_flags(device_t brdev, device_t child, int type, int rid,
    u_long flags)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	struct resource *res;

	if (type != SYS_RES_MEMORY)
		return (EINVAL);
	res = cbb_find_res(sc, type, rid);
	if (res == NULL) {
		device_printf(brdev,
		    "set_res_flags: specified rid not found\n");
		return (ENOENT);
	}
	return (exca_mem_set_flags(&sc->exca[0], res, flags));
}