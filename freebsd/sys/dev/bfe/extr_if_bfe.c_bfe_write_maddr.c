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
struct sockaddr_dl {int dummy; } ;
struct bfe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  bfe_cam_write (struct bfe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u_int
bfe_write_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct bfe_softc *sc = arg;

	bfe_cam_write(sc, LLADDR(sdl), cnt + 1);

	return (1);
}