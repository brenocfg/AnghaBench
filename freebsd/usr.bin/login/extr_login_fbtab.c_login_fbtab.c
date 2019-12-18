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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  LOG_ERR ; 
 char* WSPACE ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 char* _PATH_FBTAB ; 
 char* _PATH_LOGINDEVPERM ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  login_protect (char const*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,char*) ; 

void
login_fbtab(char *tty, uid_t uid, gid_t gid)
{
    FILE   *fp;
    char    buf[BUFSIZ];
    char   *devname;
    char   *cp;
    int     prot;
    const char *table;

    if ((fp = fopen(table = _PATH_FBTAB, "r")) == NULL
    && (fp = fopen(table = _PATH_LOGINDEVPERM, "r")) == NULL)
	return;

    while (fgets(buf, sizeof(buf), fp)) {
	if ((cp = strchr(buf, '#')))
	    *cp = 0;				/* strip comment */
	if ((cp = devname = strtok(buf, WSPACE)) == NULL)
	    continue;				/* empty or comment */
	if (strncmp(devname, _PATH_DEV, sizeof _PATH_DEV - 1) != 0
	       || (cp = strtok(NULL, WSPACE)) == NULL
	       || *cp != '0'
	       || sscanf(cp, "%o", &prot) == 0
	       || prot == 0
	       || (prot & 0777) != prot
	       || (cp = strtok(NULL, WSPACE)) == NULL) {
	    syslog(LOG_ERR, "%s: bad entry: %s", table, cp ? cp : "(null)");
	    continue;
	}
	if (strcmp(devname + 5, tty) == 0) {
	    for (cp = strtok(cp, ":"); cp; cp = strtok(NULL, ":")) {
		login_protect(table, cp, prot, uid, gid);
	    }
	}
    }
    fclose(fp);
}