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
struct smbioc_oshare {int /*<<< orphan*/  ioc_password; int /*<<< orphan*/  ioc_stype; int /*<<< orphan*/  ioc_share; int /*<<< orphan*/  ioc_group; int /*<<< orphan*/  ioc_owner; int /*<<< orphan*/  ioc_rights; int /*<<< orphan*/  ioc_mode; } ;
struct smb_sharespec {int /*<<< orphan*/  pass; int /*<<< orphan*/  stype; int /*<<< orphan*/  name; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; int /*<<< orphan*/  rights; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct smb_sharespec*,int) ; 

__attribute__((used)) static int
smb_usr_share2spec(struct smbioc_oshare *dp, struct smb_sharespec *spec)
{
	bzero(spec, sizeof(*spec));
	spec->mode = dp->ioc_mode;
	spec->rights = dp->ioc_rights;
	spec->owner = dp->ioc_owner;
	spec->group = dp->ioc_group;
	spec->name = dp->ioc_share;
	spec->stype = dp->ioc_stype;
	spec->pass = dp->ioc_password;
	return 0;
}