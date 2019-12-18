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
struct smb_ctx {int /*<<< orphan*/ * ct_srvaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
smb_ctx_setsrvaddr(struct smb_ctx *ctx, const char *addr)
{
	if (addr == NULL || addr[0] == 0)
		return EINVAL;
	if (ctx->ct_srvaddr)
		free(ctx->ct_srvaddr);
	if ((ctx->ct_srvaddr = strdup(addr)) == NULL)
		return ENOMEM;
	return 0;
}