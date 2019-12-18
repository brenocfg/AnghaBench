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
struct stat {scalar_t__ st_ino; int st_nlink; } ;
struct ViceIoctl {char* out; char* in; int out_size; scalar_t__ in_size; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  VIOC_AFS_STAT_MT_PT ; 
 scalar_t__ do_the_afs_dance ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ k_hasafs () ; 
 int k_pioctl (char*,int /*<<< orphan*/ ,struct ViceIoctl*,int /*<<< orphan*/ ) ; 
 int lstat (char const*,struct stat*) ; 
 char* malloc (int const) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int
lstat_file (const char *file, struct stat *sb)
{
#ifdef KRB5
    if (do_the_afs_dance &&
	k_hasafs()
	&& strcmp(file, ".")
	&& strcmp(file, "..")
	&& strcmp(file, "/"))
    {
	struct ViceIoctl    a_params;
	char               *dir, *last;
	char               *path_bkp;
	static ino_t	   ino_counter = 0, ino_last = 0;
	int		   ret;
	const int	   maxsize = 2048;

	path_bkp = strdup (file);
	if (path_bkp == NULL)
	    return -1;

	a_params.out = malloc (maxsize);
	if (a_params.out == NULL) {
	    free (path_bkp);
	    return -1;
	}

	/* If path contains more than the filename alone - split it */

	last = strrchr (path_bkp, '/');
	if (last != NULL) {
	    if(last[1] == '\0')
		/* if path ended in /, replace with `.' */
		a_params.in = ".";
	    else
		a_params.in = last + 1;
	    while(last > path_bkp && *--last == '/');
	    if(*last != '/' || last != path_bkp) {
		*++last = '\0';
		dir = path_bkp;
	    } else
		/* we got to the start, so this must be the root dir */
		dir = "/";
	} else {
	    /* file is relative to cdir */
	    dir = ".";
	    a_params.in = path_bkp;
	}

	a_params.in_size  = strlen (a_params.in) + 1;
	a_params.out_size = maxsize;

	ret = k_pioctl (dir, VIOC_AFS_STAT_MT_PT, &a_params, 0);
	free (a_params.out);
	if (ret < 0) {
	    free (path_bkp);

	    if (errno != EINVAL)
		return ret;
	    else
		/* if we get EINVAL this is probably not a mountpoint */
		return lstat (file, sb);
	}

	/*
	 * wow this was a mountpoint, lets cook the struct stat
	 * use . as a prototype
	 */

	ret = lstat (dir, sb);
	free (path_bkp);
	if (ret < 0)
	    return ret;

	if (ino_last == sb->st_ino)
	    ino_counter++;
	else {
	    ino_last    = sb->st_ino;
	    ino_counter = 0;
	}
	sb->st_ino += ino_counter;
	sb->st_nlink = 3;

	return 0;
    }
#endif /* KRB5 */
    return lstat (file, sb);
}