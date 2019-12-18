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
struct smbnode {int dummy; } ;
struct smbfs_fctx {int f_attrmask; char* f_wildcard; int f_wclen; int /*<<< orphan*/  f_fname; int /*<<< orphan*/  f_name; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
smbfs_findopenLM1(struct smbfs_fctx *ctx, struct smbnode *dnp,
	const char *wildcard, int wclen, int attr, struct smb_cred *scred)
{
	ctx->f_attrmask = attr;
	if (wildcard) {
		if (wclen == 1 && wildcard[0] == '*') {
			ctx->f_wildcard = "*.*";
			ctx->f_wclen = 3;
		} else {
			ctx->f_wildcard = wildcard;
			ctx->f_wclen = wclen;
		}
	} else {
		ctx->f_wildcard = NULL;
		ctx->f_wclen = 0;
	}
	ctx->f_name = ctx->f_fname;
	return 0;
}