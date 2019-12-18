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
typedef  int u_int ;
struct vge_softc {scalar_t__ vge_camidx; } ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 scalar_t__ VGE_CAM_MAXADDRS ; 
 int /*<<< orphan*/  vge_cam_set (struct vge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
vge_set_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct vge_softc *sc = arg;

        if (sc->vge_camidx == VGE_CAM_MAXADDRS)
		return (0);

	(void )vge_cam_set(sc, LLADDR(sdl));

	return (1);
}