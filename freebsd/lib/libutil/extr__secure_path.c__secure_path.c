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
typedef  scalar_t__ uid_t ;
struct stat {int st_mode; scalar_t__ st_uid; scalar_t__ st_gid; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 scalar_t__ errno ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char const*,char*,char const*,scalar_t__) ; 

int
_secure_path(const char *path, uid_t uid, gid_t gid)
{
    int		r = -1;
    struct stat	sb;
    const char	*msg = NULL;

    if (lstat(path, &sb) < 0) {
	if (errno == ENOENT) /* special case */
	    r = -2;  /* if it is just missing, skip the log entry */
	else
	    msg = "%s: cannot stat %s: %m";
    }
    else if (!S_ISREG(sb.st_mode))
    	msg = "%s: %s is not a regular file";
    else if (sb.st_mode & S_IWOTH)
    	msg = "%s: %s is world writable";
    else if ((int)uid != -1 && sb.st_uid != uid && sb.st_uid != 0) {
    	if (uid == 0)
    		msg = "%s: %s is not owned by root";
    	else
    		msg = "%s: %s is not owned by uid %d";
    } else if ((int)gid != -1 && sb.st_gid != gid && (sb.st_mode & S_IWGRP))
    	msg = "%s: %s is group writeable by non-authorised groups";
    else
    	r = 0;
    if (msg != NULL)
	syslog(LOG_ERR, msg, "_secure_path", path, uid);
    return r;
}