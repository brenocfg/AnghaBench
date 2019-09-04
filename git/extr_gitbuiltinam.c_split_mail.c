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
struct am_state {int dummy; } ;
typedef  enum patch_format { ____Placeholder_patch_format } patch_format ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  PATCH_FORMAT_HG 132 
#define  PATCH_FORMAT_MBOX 131 
#define  PATCH_FORMAT_MBOXRD 130 
#define  PATCH_FORMAT_STGIT 129 
#define  PATCH_FORMAT_STGIT_SERIES 128 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int /*<<< orphan*/  hg_patch_to_mail ; 
 int split_mail_conv (int /*<<< orphan*/ ,struct am_state*,char const**,int) ; 
 int split_mail_mbox (struct am_state*,char const**,int,int) ; 
 int split_mail_stgit_series (struct am_state*,char const**,int) ; 
 int /*<<< orphan*/  stgit_patch_to_mail ; 

__attribute__((used)) static int split_mail(struct am_state *state, enum patch_format patch_format,
			const char **paths, int keep_cr)
{
	if (keep_cr < 0) {
		keep_cr = 0;
		git_config_get_bool("am.keepcr", &keep_cr);
	}

	switch (patch_format) {
	case PATCH_FORMAT_MBOX:
		return split_mail_mbox(state, paths, keep_cr, 0);
	case PATCH_FORMAT_STGIT:
		return split_mail_conv(stgit_patch_to_mail, state, paths, keep_cr);
	case PATCH_FORMAT_STGIT_SERIES:
		return split_mail_stgit_series(state, paths, keep_cr);
	case PATCH_FORMAT_HG:
		return split_mail_conv(hg_patch_to_mail, state, paths, keep_cr);
	case PATCH_FORMAT_MBOXRD:
		return split_mail_mbox(state, paths, keep_cr, 1);
	default:
		BUG("invalid patch_format");
	}
	return -1;
}