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
typedef  int /*<<< orphan*/  uint64_t ;
struct passwd {char* pw_name; int pw_fields; char* pw_passwd; char* pw_class; char* pw_gecos; char* pw_dir; char* pw_shell; scalar_t__ pw_expire; scalar_t__ pw_change; scalar_t__ pw_gid; scalar_t__ pw_uid; } ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int _PWF_CHANGE ; 
 int _PWF_CLASS ; 
 int _PWF_DIR ; 
 int _PWF_EXPIRE ; 
 int _PWF_GECOS ; 
 int _PWF_GID ; 
 int _PWF_NAME ; 
 int _PWF_PASSWD ; 
 int _PWF_SHELL ; 
 int _PWF_UID ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ pwd_allowed_field (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  pwd_allowed_user (int /*<<< orphan*/  const*,char*,scalar_t__) ; 

__attribute__((used)) static bool
pwd_pack(const nvlist_t *limits, const struct passwd *pwd, nvlist_t *nvl)
{
	int fields;

	if (pwd == NULL)
		return (true);

	/*
	 * If either name or UID is allowed, we allow it.
	 */
	if (!pwd_allowed_user(limits, pwd->pw_name, pwd->pw_uid))
		return (false);

	fields = pwd->pw_fields;

	if (pwd_allowed_field(limits, "pw_name")) {
		nvlist_add_string(nvl, "pw_name", pwd->pw_name);
	} else {
		nvlist_add_string(nvl, "pw_name", "");
		fields &= ~_PWF_NAME;
	}
	if (pwd_allowed_field(limits, "pw_uid")) {
		nvlist_add_number(nvl, "pw_uid", (uint64_t)pwd->pw_uid);
	} else {
		nvlist_add_number(nvl, "pw_uid", (uint64_t)-1);
		fields &= ~_PWF_UID;
	}
	if (pwd_allowed_field(limits, "pw_gid")) {
		nvlist_add_number(nvl, "pw_gid", (uint64_t)pwd->pw_gid);
	} else {
		nvlist_add_number(nvl, "pw_gid", (uint64_t)-1);
		fields &= ~_PWF_GID;
	}
	if (pwd_allowed_field(limits, "pw_change")) {
		nvlist_add_number(nvl, "pw_change", (uint64_t)pwd->pw_change);
	} else {
		nvlist_add_number(nvl, "pw_change", (uint64_t)0);
		fields &= ~_PWF_CHANGE;
	}
	if (pwd_allowed_field(limits, "pw_passwd")) {
		nvlist_add_string(nvl, "pw_passwd", pwd->pw_passwd);
	} else {
		nvlist_add_string(nvl, "pw_passwd", "");
		fields &= ~_PWF_PASSWD;
	}
	if (pwd_allowed_field(limits, "pw_class")) {
		nvlist_add_string(nvl, "pw_class", pwd->pw_class);
	} else {
		nvlist_add_string(nvl, "pw_class", "");
		fields &= ~_PWF_CLASS;
	}
	if (pwd_allowed_field(limits, "pw_gecos")) {
		nvlist_add_string(nvl, "pw_gecos", pwd->pw_gecos);
	} else {
		nvlist_add_string(nvl, "pw_gecos", "");
		fields &= ~_PWF_GECOS;
	}
	if (pwd_allowed_field(limits, "pw_dir")) {
		nvlist_add_string(nvl, "pw_dir", pwd->pw_dir);
	} else {
		nvlist_add_string(nvl, "pw_dir", "");
		fields &= ~_PWF_DIR;
	}
	if (pwd_allowed_field(limits, "pw_shell")) {
		nvlist_add_string(nvl, "pw_shell", pwd->pw_shell);
	} else {
		nvlist_add_string(nvl, "pw_shell", "");
		fields &= ~_PWF_SHELL;
	}
	if (pwd_allowed_field(limits, "pw_expire")) {
		nvlist_add_number(nvl, "pw_expire", (uint64_t)pwd->pw_expire);
	} else {
		nvlist_add_number(nvl, "pw_expire", (uint64_t)0);
		fields &= ~_PWF_EXPIRE;
	}
	nvlist_add_number(nvl, "pw_fields", (uint64_t)fields);

	return (true);
}