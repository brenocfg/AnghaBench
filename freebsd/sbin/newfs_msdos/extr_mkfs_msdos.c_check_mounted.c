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
struct statfs {char* f_mntfromname; int /*<<< orphan*/  f_mntonname; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_NOWAIT ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_mounted(const char *fname, mode_t mode)
{
    struct statfs *mp;
    const char *s1, *s2;
    size_t len;
    int n, r;

    if (!(n = getmntinfo(&mp, MNT_NOWAIT))) {
	warn("getmntinfo");
	return -1;
    }
    len = strlen(_PATH_DEV);
    s1 = fname;
    if (!strncmp(s1, _PATH_DEV, len))
	s1 += len;
    r = S_ISCHR(mode) && s1 != fname && *s1 == 'r';
    for (; n--; mp++) {
	s2 = mp->f_mntfromname;
	if (!strncmp(s2, _PATH_DEV, len))
	    s2 += len;
	if ((r && s2 != mp->f_mntfromname && !strcmp(s1 + 1, s2)) ||
	    !strcmp(s1, s2)) {
	    warnx("%s is mounted on %s", fname, mp->f_mntonname);
	    return -1;
	}
    }
    return 0;
}