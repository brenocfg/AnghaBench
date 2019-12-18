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
typedef  int u_int64_t ;
struct sshbuf {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_fields; int /*<<< orphan*/  pw_expire; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_class; int /*<<< orphan*/  pw_gecos; int /*<<< orphan*/  pw_change; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_passwd; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sshbuf_free_passwd (struct passwd*) ; 
 scalar_t__ sshbuf_get_cstring (struct sshbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_get_time (struct sshbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ sshbuf_get_u32 (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int sshbuf_get_u64 (struct sshbuf*,int*) ; 
 struct passwd* xcalloc (int,int) ; 

struct passwd *
sshbuf_get_passwd(struct sshbuf *buf)
{
	struct passwd *pw;
	u_int64_t len;
	int r;

	/* check if size of struct passwd is as same as sender's size */
	r = sshbuf_get_u64(buf, &len);
	if (r != 0 || len != sizeof(*pw))
		return NULL;

	pw = xcalloc(1, sizeof(*pw));
	if (sshbuf_get_cstring(buf, &pw->pw_name, NULL) != 0 ||
	    sshbuf_get_cstring(buf, &pw->pw_passwd, NULL) != 0 ||
	    sshbuf_get_u32(buf, &pw->pw_uid) != 0 ||
	    sshbuf_get_u32(buf, &pw->pw_gid) != 0 ||
#ifdef HAVE_STRUCT_PASSWD_PW_CHANGE
	    sshbuf_get_time(buf, &pw->pw_change) != 0 ||
#endif
#ifdef HAVE_STRUCT_PASSWD_PW_GECOS
	    sshbuf_get_cstring(buf, &pw->pw_gecos, NULL) != 0 ||
#endif
#ifdef HAVE_STRUCT_PASSWD_PW_CLASS
	    sshbuf_get_cstring(buf, &pw->pw_class, NULL) != 0 ||
#endif
	    sshbuf_get_cstring(buf, &pw->pw_dir, NULL) != 0 ||
	    sshbuf_get_cstring(buf, &pw->pw_shell, NULL) != 0 ||
#ifdef HAVE_STRUCT_PASSWD_PW_EXPIRE
	    sshbuf_get_time(buf, &pw->pw_expire) != 0 ||
#endif
	    sshbuf_get_u32(buf, &pw->pw_fields) != 0) {
		sshbuf_free_passwd(pw);
		return NULL;
	}
	return pw;
}