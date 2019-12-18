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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_long ;
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ intmax_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int E_BADINF ; 
 int E_CHKSUM ; 
 int E_ERRNO ; 
 int E_LENGTH ; 
 int E_NAME ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ close (int) ; 
 scalar_t__ crc (int,scalar_t__*,scalar_t__*) ; 
 char* distname (char const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ isfatal (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_all ; 
 int /*<<< orphan*/  opt_exist ; 
 scalar_t__ opt_ignore ; 
 int report (char const*,char const*,int) ; 
 int sscanf (char*,char*,...) ; 
 int /*<<< orphan*/ * stdin ; 

__attribute__((used)) static int
chkinf(FILE * fp, const char *path)
{
    char buf[30];               /* "cksum.2 = 10 6" */
    char ext[3];
    struct stat sb;
    const char *dname;
    off_t len;
    u_long sum;
    intmax_t sumlen;
    uint32_t chk;
    int rval, error, c, pieces, cnt, fd;
    char ch;

    rval = 0;
    for (cnt = -1; fgets(buf, sizeof(buf), fp); cnt++) {
	fd = -1;
	dname = NULL;
	error = 0;
	if (cnt == -1) {
	    if ((c = sscanf(buf, "Pieces =  %d%c", &pieces, &ch)) != 2 ||
		ch != '\n' || pieces < 1)
		error = E_BADINF;
	} else if (((c = sscanf(buf, "cksum.%2s = %lu %jd%c", ext, &sum,
			        &sumlen, &ch)) != 4 &&
		    (!feof(fp) || c != 3)) || (c == 4 && ch != '\n') ||
		   ext[0] != 'a' + cnt / 26 || ext[1] != 'a' + cnt % 26)
	    error = E_BADINF;
	else if ((dname = distname(fp == stdin ? NULL : path, NULL,
				    ext)) == NULL)
	    error = E_NAME;
	else if ((fd = open(dname, O_RDONLY)) == -1)
	    error = E_ERRNO;
	else if (fstat(fd, &sb))
	    error = E_ERRNO;
	else if (sb.st_size != (off_t)sumlen)
	    error = E_LENGTH;
	else if (!opt_exist) {
	    if (crc(fd, &chk, &len))
		error = E_ERRNO;
	    else if (chk != sum)
		error = E_CHKSUM;
	}
	if (fd != -1 && close(fd))
	    err(2, "%s", dname);
	if (opt_ignore && error == E_ERRNO && errno == ENOENT)
	    continue;
	if (error || (opt_all && cnt >= 0))
	    rval |= report(path, dname, error);
	if (isfatal(error))
	    break;
    }
    return rval;
}