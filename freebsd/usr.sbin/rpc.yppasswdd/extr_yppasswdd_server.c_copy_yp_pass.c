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
struct TYPE_2__ {int /*<<< orphan*/  pw_fields; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_gecos; void* pw_expire; void* pw_change; int /*<<< orphan*/  pw_class; void* pw_gid; void* pw_uid; int /*<<< orphan*/  pw_passwd; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PWF_CHANGE ; 
 int /*<<< orphan*/  _PWF_CLASS ; 
 int /*<<< orphan*/  _PWF_DIR ; 
 int /*<<< orphan*/  _PWF_EXPIRE ; 
 int /*<<< orphan*/  _PWF_GECOS ; 
 int /*<<< orphan*/  _PWF_GID ; 
 int /*<<< orphan*/  _PWF_NAME ; 
 int /*<<< orphan*/  _PWF_PASSWD ; 
 int /*<<< orphan*/  _PWF_SHELL ; 
 int /*<<< orphan*/  _PWF_UID ; 
 void* atoi (char*) ; 
 void* atol (char*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 char* realloc (char*,int) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 TYPE_1__ yp_password ; 

__attribute__((used)) static void
copy_yp_pass(char *p, int x, int m)
{
	char *t, *s = p;
	static char *buf;

	yp_password.pw_fields = 0;

	buf = realloc(buf, m + 10);
	bzero(buf, m + 10);

	/* Turn all colons into NULLs */
	while (strchr(s, ':')) {
		s = (strchr(s, ':') + 1);
		*(s - 1)= '\0';
	}

	t = buf;
#define EXPAND(e) do { \
	e = t; \
	while ((*t++ = *p++)); \
} while (0)
        EXPAND(yp_password.pw_name);
	yp_password.pw_fields |= _PWF_NAME;
        EXPAND(yp_password.pw_passwd);
	yp_password.pw_fields |= _PWF_PASSWD;
	yp_password.pw_uid = atoi(p);
        p += (strlen(p) + 1);
	yp_password.pw_fields |= _PWF_UID;
	yp_password.pw_gid = atoi(p);
        p += (strlen(p) + 1);
	yp_password.pw_fields |= _PWF_GID;
	if (x) {
		EXPAND(yp_password.pw_class);
		yp_password.pw_fields |= _PWF_CLASS;
		yp_password.pw_change = atol(p);
		p += (strlen(p) + 1);
		yp_password.pw_fields |= _PWF_CHANGE;
		yp_password.pw_expire = atol(p);
		p += (strlen(p) + 1);
		yp_password.pw_fields |= _PWF_EXPIRE;
	}
        EXPAND(yp_password.pw_gecos);
	yp_password.pw_fields |= _PWF_GECOS;
        EXPAND(yp_password.pw_dir);
	yp_password.pw_fields |= _PWF_DIR;
        EXPAND(yp_password.pw_shell);
	yp_password.pw_fields |= _PWF_SHELL;

	return;
}