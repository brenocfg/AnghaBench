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
struct rcfile {int dummy; } ;
struct nb_ctx {int /*<<< orphan*/  nb_timo; } ;

/* Variables and functions */
 int EINVAL ; 
 int nb_ctx_setns (struct nb_ctx*,char*) ; 
 int /*<<< orphan*/  nb_ctx_setscope (struct nb_ctx*,char*) ; 
 int /*<<< orphan*/  rc_getint (struct rcfile*,char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_getstringptr (struct rcfile*,char const*,char*,char**) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ,char const*) ; 

int
nb_ctx_readrcsection(struct rcfile *rcfile, struct nb_ctx *ctx,
	const char *sname, int level)
{
	char *p;
	int error;

	if (level > 1)
		return EINVAL;
	rc_getint(rcfile, sname, "nbtimeout", &ctx->nb_timo);
	rc_getstringptr(rcfile, sname, "nbns", &p);
	if (p) {
		error = nb_ctx_setns(ctx, p);
		if (error) {
			smb_error("invalid address specified in the section %s", 0, sname);
			return error;
		}
	}
	rc_getstringptr(rcfile, sname, "nbscope", &p);
	if (p)
		nb_ctx_setscope(ctx, p);
	return 0;
}