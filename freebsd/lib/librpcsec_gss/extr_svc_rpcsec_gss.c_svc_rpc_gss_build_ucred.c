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
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_2__ {int uid; int gid; int gidlen; int /*<<< orphan*/  gidlist; } ;
struct svc_rpc_gss_client {int /*<<< orphan*/  cl_gid_storage; int /*<<< orphan*/  cl_mech; TYPE_1__ cl_ucred; } ;
struct passwd {int pw_uid; int pw_gid; int /*<<< orphan*/  pw_name; } ;
typedef  TYPE_1__ rpc_gss_ucred_t ;
typedef  int /*<<< orphan*/  gss_name_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_S_COMPLETE ; 
 int NGRPS ; 
 int /*<<< orphan*/  getgrouplist (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,int,struct passwd**) ; 
 scalar_t__ gss_pname_to_uid (scalar_t__*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
svc_rpc_gss_build_ucred(struct svc_rpc_gss_client *client,
    const gss_name_t name)
{
	OM_uint32		maj_stat, min_stat;
	char			buf[128];
	uid_t			uid;
	struct passwd		pwd, *pw;
	rpc_gss_ucred_t		*uc = &client->cl_ucred;

	uc->uid = 65534;
	uc->gid = 65534;
	uc->gidlen = 0;
	uc->gidlist = client->cl_gid_storage;

	maj_stat = gss_pname_to_uid(&min_stat, name, client->cl_mech, &uid);
	if (maj_stat != GSS_S_COMPLETE)
		return;

	getpwuid_r(uid, &pwd, buf, sizeof(buf), &pw);
	if (pw) {
		int len = NGRPS;
		uc->uid = pw->pw_uid;
		uc->gid = pw->pw_gid;
		uc->gidlist = client->cl_gid_storage;
		getgrouplist(pw->pw_name, pw->pw_gid, uc->gidlist, &len);
		uc->gidlen = len;
	}
}