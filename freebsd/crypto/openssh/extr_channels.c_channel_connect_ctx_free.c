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
struct channel_connect {TYPE_1__* aitop; TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ ai_family; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  freeaddrinfo (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct channel_connect*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
channel_connect_ctx_free(struct channel_connect *cctx)
{
	free(cctx->host);
	if (cctx->aitop) {
		if (cctx->aitop->ai_family == AF_UNIX)
			free(cctx->aitop);
		else
			freeaddrinfo(cctx->aitop);
	}
	memset(cctx, 0, sizeof(*cctx));
}