#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_4__ {unsigned int gl_pathc; char** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  GLOB_NOSORT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ chflags (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ chmod (char*,int) ; 
 scalar_t__ chown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,char*) ; 

__attribute__((used)) static void
login_protect(const char *table, char *pattern, int mask, uid_t uid, gid_t gid)
{
    glob_t  gl;
    char   *path;
    unsigned int     i;

    if (glob(pattern, GLOB_NOSORT, NULL, &gl) != 0)
	return;
    for (i = 0; i < gl.gl_pathc; i++) {
	path = gl.gl_pathv[i];
	/* clear flags of the device */
	if (chflags(path, 0) && errno != ENOENT && errno != EOPNOTSUPP)
	    syslog(LOG_ERR, "%s: chflags(%s): %m", table, path);
	if (chmod(path, mask) && errno != ENOENT)
	    syslog(LOG_ERR, "%s: chmod(%s): %m", table, path);
	if (chown(path, uid, gid) && errno != ENOENT)
	    syslog(LOG_ERR, "%s: chown(%s): %m", table, path);
    }
    globfree(&gl);
}