#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/ * shell; int /*<<< orphan*/ * homedir; int /*<<< orphan*/ * username; } ;
typedef  TYPE_1__ uv_passwd_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_shell; int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_name; } ;

/* Variables and functions */
 int ERANGE ; 
 int UV_EINVAL ; 
 int UV_ENOENT ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  _SC_GETPW_R_SIZE_MAX ; 
 int /*<<< orphan*/  geteuid () ; 
 int getpwuid_r (int /*<<< orphan*/ ,struct passwd*,char*,size_t,struct passwd**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__free (char*) ; 
 void* uv__malloc (size_t) ; 

int uv__getpwuid_r(uv_passwd_t* pwd) {
  struct passwd pw;
  struct passwd* result;
  char* buf;
  uid_t uid;
  size_t bufsize;
  size_t name_size;
  size_t homedir_size;
  size_t shell_size;
  long initsize;
  int r;
#if defined(__ANDROID_API__) && __ANDROID_API__ < 21
  int (*getpwuid_r)(uid_t, struct passwd*, char*, size_t, struct passwd**);

  getpwuid_r = dlsym(RTLD_DEFAULT, "getpwuid_r");
  if (getpwuid_r == NULL)
    return UV_ENOSYS;
#endif

  if (pwd == NULL)
    return UV_EINVAL;

  initsize = sysconf(_SC_GETPW_R_SIZE_MAX);

  if (initsize <= 0)
    bufsize = 4096;
  else
    bufsize = (size_t) initsize;

  uid = geteuid();
  buf = NULL;

  for (;;) {
    uv__free(buf);
    buf = uv__malloc(bufsize);

    if (buf == NULL)
      return UV_ENOMEM;

    r = getpwuid_r(uid, &pw, buf, bufsize, &result);

    if (r != ERANGE)
      break;

    bufsize *= 2;
  }

  if (r != 0) {
    uv__free(buf);
    return -r;
  }

  if (result == NULL) {
    uv__free(buf);
    return UV_ENOENT;
  }

  /* Allocate memory for the username, shell, and home directory */
  name_size = strlen(pw.pw_name) + 1;
  homedir_size = strlen(pw.pw_dir) + 1;
  shell_size = strlen(pw.pw_shell) + 1;
  pwd->username = uv__malloc(name_size + homedir_size + shell_size);

  if (pwd->username == NULL) {
    uv__free(buf);
    return UV_ENOMEM;
  }

  /* Copy the username */
  memcpy(pwd->username, pw.pw_name, name_size);

  /* Copy the home directory */
  pwd->homedir = pwd->username + name_size;
  memcpy(pwd->homedir, pw.pw_dir, homedir_size);

  /* Copy the shell */
  pwd->shell = pwd->homedir + homedir_size;
  memcpy(pwd->shell, pw.pw_shell, shell_size);

  /* Copy the uid and gid */
  pwd->uid = pw.pw_uid;
  pwd->gid = pw.pw_gid;

  uv__free(buf);

  return 0;
}