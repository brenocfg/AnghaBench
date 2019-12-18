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
struct vr_hash_maddr_cam_ctx {scalar_t__ error; int mask; int /*<<< orphan*/  sc; } ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  VR_MCAST_CAM ; 
 scalar_t__ vr_cam_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
vr_hash_maddr_cam(void *arg, struct sockaddr_dl *sdl, u_int mcnt)
{
	struct vr_hash_maddr_cam_ctx *ctx = arg;

	if (ctx->error != 0)
		return (0);
	ctx->error = vr_cam_data(ctx->sc, VR_MCAST_CAM, mcnt, LLADDR(sdl));
	if (ctx->error != 0) {
		ctx->mask = 0;
		return (0);
	}
	ctx->mask |= 1 << mcnt;

	return (1);
}