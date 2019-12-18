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
struct smbioc_ossn {scalar_t__* ioc_user; scalar_t__* ioc_localcs; int ioc_opt; int /*<<< orphan*/  ioc_servercs; int /*<<< orphan*/  ioc_group; int /*<<< orphan*/  ioc_owner; int /*<<< orphan*/  ioc_rights; int /*<<< orphan*/  ioc_mode; int /*<<< orphan*/  ioc_workgroup; int /*<<< orphan*/  ioc_password; int /*<<< orphan*/  ioc_srvname; int /*<<< orphan*/  ioc_lolen; int /*<<< orphan*/ * ioc_local; int /*<<< orphan*/  ioc_svlen; int /*<<< orphan*/ * ioc_server; } ;
struct smb_vcspec {scalar_t__* username; scalar_t__* localcs; int flags; int /*<<< orphan*/  servercs; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; int /*<<< orphan*/  rights; int /*<<< orphan*/  mode; int /*<<< orphan*/  domain; int /*<<< orphan*/  pass; int /*<<< orphan*/  srvname; int /*<<< orphan*/ * lap; int /*<<< orphan*/ * sap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SMBERROR (char*) ; 
 int SMBVOPT_PRIVATE ; 
 int SMBVOPT_SINGLESHARE ; 
 int SMBV_PRIVATE ; 
 int SMBV_SINGLESHARE ; 
 int /*<<< orphan*/  bzero (struct smb_vcspec*,int) ; 
 void* smb_memdupin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_usr_vcspec_free (struct smb_vcspec*) ; 

__attribute__((used)) static int
smb_usr_vc2spec(struct smbioc_ossn *dp, struct smb_vcspec *spec)
{
	int flags = 0;

	bzero(spec, sizeof(*spec));

#ifdef NETSMB_NO_ANON_USER
	if (dp->ioc_user[0] == 0)
		return EINVAL;
#endif

	if (dp->ioc_server == NULL)
		return EINVAL;
	if (dp->ioc_localcs[0] == 0) {
		SMBERROR("no local charset ?\n");
		return EINVAL;
	}

	spec->sap = smb_memdupin(dp->ioc_server, dp->ioc_svlen);
	if (spec->sap == NULL)
		return ENOMEM;
	if (dp->ioc_local) {
		spec->lap = smb_memdupin(dp->ioc_local, dp->ioc_lolen);
		if (spec->lap == NULL) {
			smb_usr_vcspec_free(spec);
			return ENOMEM;
		}
	}
	spec->srvname = dp->ioc_srvname;
	spec->pass = dp->ioc_password;
	spec->domain = dp->ioc_workgroup;
	spec->username = dp->ioc_user;
	spec->mode = dp->ioc_mode;
	spec->rights = dp->ioc_rights;
	spec->owner = dp->ioc_owner;
	spec->group = dp->ioc_group;
	spec->localcs = dp->ioc_localcs;
	spec->servercs = dp->ioc_servercs;
	if (dp->ioc_opt & SMBVOPT_PRIVATE)
		flags |= SMBV_PRIVATE;
	if (dp->ioc_opt & SMBVOPT_SINGLESHARE)
		flags |= SMBV_PRIVATE | SMBV_SINGLESHARE;
	spec->flags = flags;
	return 0;
}