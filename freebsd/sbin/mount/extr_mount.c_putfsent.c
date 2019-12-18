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
struct statfs {int f_flags; char* f_mntfromname; char* f_mntonname; char* f_fstypename; } ;
struct fstab {int fs_freq; int fs_passno; } ;

/* Variables and functions */
 int MNT_RDONLY ; 
 char* catopt (char*,char*) ; 
 char* flags2opts (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct fstab* getfsfile (char*) ; 
 struct fstab* getfsspec (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strnstr (char*,char*,int) ; 

void
putfsent(struct statfs *ent)
{
	struct fstab *fst;
	char *opts, *rw;
	int l;

	opts = NULL;
	/* flags2opts() doesn't return the "rw" option. */
	if ((ent->f_flags & MNT_RDONLY) != 0)
		rw = NULL;
	else
		rw = catopt(NULL, "rw");

	opts = flags2opts(ent->f_flags);
	opts = catopt(rw, opts);

	if (strncmp(ent->f_mntfromname, "<below>", 7) == 0 ||
	    strncmp(ent->f_mntfromname, "<above>", 7) == 0) {
		strlcpy(ent->f_mntfromname,
		    (strnstr(ent->f_mntfromname, ":", 8) +1),
		    sizeof(ent->f_mntfromname));
	}

	l = strlen(ent->f_mntfromname);
	printf("%s%s%s%s", ent->f_mntfromname,
	    l < 8 ? "\t" : "",
	    l < 16 ? "\t" : "",
	    l < 24 ? "\t" : " ");
	l = strlen(ent->f_mntonname);
	printf("%s%s%s%s", ent->f_mntonname,
	    l < 8 ? "\t" : "",
	    l < 16 ? "\t" : "",
	    l < 24 ? "\t" : " ");
	printf("%s\t", ent->f_fstypename);
	l = strlen(opts);
	printf("%s%s", opts,
	    l < 8 ? "\t" : " ");
	free(opts);

	if ((fst = getfsspec(ent->f_mntfromname)))
		printf("\t%u %u\n", fst->fs_freq, fst->fs_passno);
	else if ((fst = getfsfile(ent->f_mntonname)))
		printf("\t%u %u\n", fst->fs_freq, fst->fs_passno);
	else if (strcmp(ent->f_fstypename, "ufs") == 0) {
		if (strcmp(ent->f_mntonname, "/") == 0)
			printf("\t1 1\n");
		else
			printf("\t2 2\n");
	} else
		printf("\t0 0\n");
}