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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int E_BADMD5 ; 
 int E_CHKSUM ; 
 int E_ERRNO ; 
 int E_NAME ; 
 int /*<<< orphan*/  MD5File (char const*,char*) ; 
 int MDSUMLEN ; 
 int /*<<< orphan*/  NAMESIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ close (int) ; 
 char* distname (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isfatal (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_all ; 
 scalar_t__ opt_exist ; 
 scalar_t__ opt_ignore ; 
 int report (char const*,char const*,int) ; 
 int sscanf (char*,char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
chkmd5(FILE * fp, const char *path)
{
    char buf[298];              /* "MD5 (NAMESIZE = MDSUMLEN" */
    char name[NAMESIZE + 1];
    char sum[MDSUMLEN + 1], chk[MDSUMLEN + 1];
    const char *dname;
    char *s;
    int rval, error, c, fd;
    char ch;

    rval = 0;
    while (fgets(buf, sizeof(buf), fp)) {
	dname = NULL;
	error = 0;
	if (((c = sscanf(buf, "MD5 (%256s = %32s%c", name, sum,
			 &ch)) != 3 && (!feof(fp) || c != 2)) ||
	    (c == 3 && ch != '\n') ||
	    (s = strrchr(name, ')')) == NULL ||
	    strlen(sum) != MDSUMLEN)
	    error = E_BADMD5;
	else {
	    *s = 0;
	    if ((dname = distname(path, name, NULL)) == NULL)
		error = E_NAME;
	    else if (opt_exist) {
		if ((fd = open(dname, O_RDONLY)) == -1)
		    error = E_ERRNO;
		else if (close(fd))
		    err(2, "%s", dname);
	    } else if (!MD5File(dname, chk))
		error = E_ERRNO;
	    else if (strcmp(chk, sum))
		error = E_CHKSUM;
	}
	if (opt_ignore && error == E_ERRNO && errno == ENOENT)
	    continue;
	if (error || opt_all)
	    rval |= report(path, dname, error);
	if (isfatal(error))
	    break;
    }
    return rval;
}