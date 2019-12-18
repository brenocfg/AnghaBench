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
typedef  scalar_t__ u_int ;
struct sockaddr_dl {int dummy; } ;
struct mclist_ctx {scalar_t__ mclistsz; scalar_t__ mclist; } ;

/* Variables and functions */
 scalar_t__ ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u_int
ndis_copy_maddr(void *arg, struct sockaddr_dl *sdl, u_int cnt)
{
	struct mclist_ctx *ctx = arg;

	if (cnt < ctx->mclistsz)
		bcopy(LLADDR(sdl), ctx->mclist + (ETHER_ADDR_LEN * cnt),
		    ETHER_ADDR_LEN);
	return (1);
}