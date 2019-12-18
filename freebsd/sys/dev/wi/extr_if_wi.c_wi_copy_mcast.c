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
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/ * wi_mcast; } ;
struct wi_mcast_ctx {int mcnt; TYPE_1__ mlist; } ;
struct sockaddr_dl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLADDR (struct sockaddr_dl*) ; 

__attribute__((used)) static u_int
wi_copy_mcast(void *arg, struct sockaddr_dl *sdl, u_int count)
{
	struct wi_mcast_ctx *ctx = arg;

	if (ctx->mcnt >= 16)
		return (0);
	IEEE80211_ADDR_COPY(&ctx->mlist.wi_mcast[ctx->mcnt++], LLADDR(sdl));

	return (1);
}