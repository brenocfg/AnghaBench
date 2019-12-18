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
typedef  int time_t ;
struct tm {int dummy; } ;
struct stat {int st_mode; int st_mtime; scalar_t__ st_size; scalar_t__ st_rdev; scalar_t__ st_gid; scalar_t__ st_uid; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_ino; } ;
struct passwd {char* pw_name; } ;
struct group {char* gr_name; } ;
struct fileinfo {char* mode; int /*<<< orphan*/ * link; int /*<<< orphan*/ * filename; int /*<<< orphan*/ * date; int /*<<< orphan*/ * size; int /*<<< orphan*/ * minor; int /*<<< orphan*/ * major; int /*<<< orphan*/ * group; int /*<<< orphan*/ * user; int /*<<< orphan*/  n_link; int /*<<< orphan*/  bsize; int /*<<< orphan*/  inode; struct stat st; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int LS_TYPE ; 
 int S_IRWXG ; 
 size_t S_IRWXO ; 
 int S_IRWXU ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 int S_ISGID ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int S_ISTXT ; 
 int S_ISUID ; 
 scalar_t__ S_ISWHT (int) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int asprintf (int /*<<< orphan*/ **,char*,...) ; 
 int /*<<< orphan*/  block_convert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 struct group* getgrgid (scalar_t__) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 struct tm* localtime (int*) ; 
 scalar_t__ major (scalar_t__) ; 
 scalar_t__ minor (scalar_t__) ; 
 int readlink (char*,char*,int) ; 
 int /*<<< orphan*/  sec_fprintf2 (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
make_fileinfo(FILE *out, const char *filename, struct fileinfo *file, int flags)
{
    char buf[128];
    int file_type = 0;
    struct stat *st = &file->st;

    file->inode = st->st_ino;
    file->bsize = block_convert(st->st_blocks);

    if(S_ISDIR(st->st_mode)) {
	file->mode[0] = 'd';
	file_type = '/';
    }
    else if(S_ISCHR(st->st_mode))
	file->mode[0] = 'c';
    else if(S_ISBLK(st->st_mode))
	file->mode[0] = 'b';
    else if(S_ISREG(st->st_mode)) {
	file->mode[0] = '-';
	if(st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
	    file_type = '*';
    }
    else if(S_ISFIFO(st->st_mode)) {
	file->mode[0] = 'p';
	file_type = '|';
    }
    else if(S_ISLNK(st->st_mode)) {
	file->mode[0] = 'l';
	file_type = '@';
    }
    else if(S_ISSOCK(st->st_mode)) {
	file->mode[0] = 's';
	file_type = '=';
    }
#ifdef S_ISWHT
    else if(S_ISWHT(st->st_mode)) {
	file->mode[0] = 'w';
	file_type = '%';
    }
#endif
    else
	file->mode[0] = '?';
    {
	char *x[] = { "---", "--x", "-w-", "-wx",
		      "r--", "r-x", "rw-", "rwx" };
	strcpy(file->mode + 1, x[(st->st_mode & S_IRWXU) >> 6]);
	strcpy(file->mode + 4, x[(st->st_mode & S_IRWXG) >> 3]);
	strcpy(file->mode + 7, x[(st->st_mode & S_IRWXO) >> 0]);
	if((st->st_mode & S_ISUID)) {
	    if((st->st_mode & S_IXUSR))
		file->mode[3] = 's';
	    else
		file->mode[3] = 'S';
	}
	if((st->st_mode & S_ISGID)) {
	    if((st->st_mode & S_IXGRP))
		file->mode[6] = 's';
	    else
		file->mode[6] = 'S';
	}
	if((st->st_mode & S_ISTXT)) {
	    if((st->st_mode & S_IXOTH))
		file->mode[9] = 't';
	    else
		file->mode[9] = 'T';
	}
    }
    file->n_link = st->st_nlink;
    {
	struct passwd *pwd;
	pwd = getpwuid(st->st_uid);
	if(pwd == NULL) {
	    if (asprintf(&file->user, "%u", (unsigned)st->st_uid) == -1)
		file->user = NULL;
	} else
	    file->user = strdup(pwd->pw_name);
	if (file->user == NULL) {
	    syslog(LOG_ERR, "out of memory");
	    return -1;
	}
    }
    {
	struct group *grp;
	grp = getgrgid(st->st_gid);
	if(grp == NULL) {
	    if (asprintf(&file->group, "%u", (unsigned)st->st_gid) == -1)
		file->group = NULL;
	} else
	    file->group = strdup(grp->gr_name);
	if (file->group == NULL) {
	    syslog(LOG_ERR, "out of memory");
	    return -1;
	}
    }

    if(S_ISCHR(st->st_mode) || S_ISBLK(st->st_mode)) {
#if defined(major) && defined(minor)
	if (asprintf(&file->major, "%u", (unsigned)major(st->st_rdev)) == -1)
	    file->major = NULL;
	if (asprintf(&file->minor, "%u", (unsigned)minor(st->st_rdev)) == -1)
	    file->minor = NULL;
#else
	/* Don't want to use the DDI/DKI crap. */
	if (asprintf(&file->major, "%u", (unsigned)st->st_rdev) == -1)
	    file->major = NULL;
	if (asprintf(&file->minor, "%u", 0) == -1)
	    file->minor = NULL;
#endif
	if (file->major == NULL || file->minor == NULL) {
	    syslog(LOG_ERR, "out of memory");
	    return -1;
	}
    } else {
	if (asprintf(&file->size, "%lu", (unsigned long)st->st_size) == -1)
	    file->size = NULL;
    }

    {
	time_t t = time(NULL);
	time_t mtime = st->st_mtime;
	struct tm *tm = localtime(&mtime);
	if((t - mtime > 6*30*24*60*60) ||
	   (mtime - t > 6*30*24*60*60))
	    strftime(buf, sizeof(buf), "%b %e  %Y", tm);
	else
	    strftime(buf, sizeof(buf), "%b %e %H:%M", tm);
	file->date = strdup(buf);
	if (file->date == NULL) {
	    syslog(LOG_ERR, "out of memory");
	    return -1;
	}
    }
    {
	const char *p = strrchr(filename, '/');
	if(p)
	    p++;
	else
	    p = filename;
	if((flags & LS_TYPE) && file_type != 0) {
	    if (asprintf(&file->filename, "%s%c", p, file_type) == -1)
		file->filename = NULL;
	} else
	    file->filename = strdup(p);
	if (file->filename == NULL) {
	    syslog(LOG_ERR, "out of memory");
	    return -1;
	}
    }
    if(S_ISLNK(st->st_mode)) {
	int n;
	n = readlink((char *)filename, buf, sizeof(buf) - 1);
	if(n >= 0) {
	    buf[n] = '\0';
	    file->link = strdup(buf);
	    if (file->link == NULL) {
		syslog(LOG_ERR, "out of memory");
		return -1;
	    }
	} else
	    sec_fprintf2(out, "readlink(%s): %s", filename, strerror(errno));
    }
    return 0;
}