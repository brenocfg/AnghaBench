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
struct smb_ctx {int ct_smbtcpport; TYPE_1__* ct_nb; } ;
struct TYPE_2__ {int nb_smbtcpport; } ;

/* Variables and functions */
 int EINVAL ; 

int
smb_ctx_setsmbport(struct smb_ctx *ctx, int port)
{
	if (port < 1 || port > 0xffff)
		return EINVAL;
	ctx->ct_smbtcpport = port;
	ctx->ct_nb->nb_smbtcpport = port;
	return 0;
}