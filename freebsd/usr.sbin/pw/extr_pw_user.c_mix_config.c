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
struct userconf {scalar_t__ default_password; scalar_t__ reuse_uids; scalar_t__ reuse_gids; scalar_t__ homemode; scalar_t__ min_uid; scalar_t__ max_uid; scalar_t__ min_gid; scalar_t__ max_gid; scalar_t__ expire_days; scalar_t__ password_days; int /*<<< orphan*/ * default_class; int /*<<< orphan*/ * groups; int /*<<< orphan*/ * default_group; int /*<<< orphan*/ * shell_default; int /*<<< orphan*/ * shells; int /*<<< orphan*/ * shelldir; int /*<<< orphan*/ * home; int /*<<< orphan*/ * logfile; int /*<<< orphan*/ * newmail; int /*<<< orphan*/ * dotdir; int /*<<< orphan*/ * nispasswd; } ;

/* Variables and functions */

__attribute__((used)) static void
mix_config(struct userconf *cmdcnf, struct userconf *cfg)
{

	if (cmdcnf->default_password < 0)
		cmdcnf->default_password = cfg->default_password;
	if (cmdcnf->reuse_uids == 0)
		cmdcnf->reuse_uids = cfg->reuse_uids;
	if (cmdcnf->reuse_gids == 0)
		cmdcnf->reuse_gids = cfg->reuse_gids;
	if (cmdcnf->nispasswd == NULL)
		cmdcnf->nispasswd = cfg->nispasswd;
	if (cmdcnf->dotdir == NULL)
		cmdcnf->dotdir = cfg->dotdir;
	if (cmdcnf->newmail == NULL)
		cmdcnf->newmail = cfg->newmail;
	if (cmdcnf->logfile == NULL)
		cmdcnf->logfile = cfg->logfile;
	if (cmdcnf->home == NULL)
		cmdcnf->home = cfg->home;
	if (cmdcnf->homemode == 0)
		cmdcnf->homemode = cfg->homemode;
	if (cmdcnf->shelldir == NULL)
		cmdcnf->shelldir = cfg->shelldir;
	if (cmdcnf->shells == NULL)
		cmdcnf->shells = cfg->shells;
	if (cmdcnf->shell_default == NULL)
		cmdcnf->shell_default = cfg->shell_default;
	if (cmdcnf->default_group == NULL)
		cmdcnf->default_group = cfg->default_group;
	if (cmdcnf->groups == NULL)
		cmdcnf->groups = cfg->groups;
	if (cmdcnf->default_class == NULL)
		cmdcnf->default_class = cfg->default_class;
	if (cmdcnf->min_uid == 0)
		cmdcnf->min_uid = cfg->min_uid;
	if (cmdcnf->max_uid == 0)
		cmdcnf->max_uid = cfg->max_uid;
	if (cmdcnf->min_gid == 0)
		cmdcnf->min_gid = cfg->min_gid;
	if (cmdcnf->max_gid == 0)
		cmdcnf->max_gid = cfg->max_gid;
	if (cmdcnf->expire_days < 0)
		cmdcnf->expire_days = cfg->expire_days;
	if (cmdcnf->password_days < 0)
		cmdcnf->password_days = cfg->password_days;
}