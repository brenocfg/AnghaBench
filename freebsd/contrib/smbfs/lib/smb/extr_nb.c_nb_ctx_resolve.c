#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int sin_len; scalar_t__ sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct nb_ctx {scalar_t__ nb_nsname; int /*<<< orphan*/  nb_flags; TYPE_2__ nb_ns; int /*<<< orphan*/  nb_nmbtcpport; int /*<<< orphan*/  nb_smbtcpport; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_BROADCAST ; 
 int /*<<< orphan*/  NBCF_RESOLVED ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (struct sockaddr*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int nb_resolvehost_in (int /*<<< orphan*/ *,struct sockaddr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_error (char*,int,scalar_t__) ; 

int
nb_ctx_resolve(struct nb_ctx *ctx)
{
	struct sockaddr *sap;
	int error;

	ctx->nb_flags &= ~NBCF_RESOLVED;

	if (ctx->nb_nsname == NULL) {
		ctx->nb_ns.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	} else {
		error = nb_resolvehost_in(ctx->nb_nsname, &sap, ctx->nb_smbtcpport);
		if (error) {
			smb_error("can't resolve %s", error, ctx->nb_nsname);
			return error;
		}
		if (sap->sa_family != AF_INET) {
			smb_error("unsupported address family %d", 0, sap->sa_family);
			return EINVAL;
		}
		bcopy(sap, &ctx->nb_ns, sizeof(ctx->nb_ns));
		free(sap);
	}
	ctx->nb_ns.sin_port = htons(ctx->nb_nmbtcpport);
	ctx->nb_ns.sin_family = AF_INET;
	ctx->nb_ns.sin_len = sizeof(ctx->nb_ns);
	ctx->nb_flags |= NBCF_RESOLVED;
	return 0;
}