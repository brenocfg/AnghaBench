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
struct mtpt_info {int mi_mode; int mi_have_mode; int mi_forced_pw; } ;
typedef  int /*<<< orphan*/  mi ;
typedef  scalar_t__ intmax_t ;
typedef  enum md_types { ____Placeholder_md_types } md_types ;

/* Variables and functions */
 int MD_MALLOC ; 
 char* MD_NAME ; 
 int MD_SWAP ; 
 int MD_VNODE ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 unsigned long ULONG_MAX ; 
 int /*<<< orphan*/  argappend (char**,char*,...) ; 
 int debug ; 
 int /*<<< orphan*/  do_copy (char const*,char const*) ; 
 int /*<<< orphan*/  do_mdconfig_attach (char*,int) ; 
 int /*<<< orphan*/  do_mdconfig_attach_au (char*,int) ; 
 int /*<<< orphan*/  do_mdconfig_detach () ; 
 int /*<<< orphan*/  do_mount_md (char*,char const*) ; 
 int /*<<< orphan*/  do_mount_tmpfs (char*,char const*) ; 
 int /*<<< orphan*/  do_mtptsetup (char const*,struct mtpt_info*) ; 
 int /*<<< orphan*/  do_newfs (char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  extract_ugid (void*,struct mtpt_info*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int getmode (void*,int) ; 
 int getopt (int,char**,char*) ; 
 char const* getprogname () ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int kldload (char*) ; 
 int loudsubs ; 
 char* mdname ; 
 int mdnamelen ; 
 char const* mdsuffix ; 
 int /*<<< orphan*/  memset (struct mtpt_info*,char,int) ; 
 int modfind (char*) ; 
 int norun ; 
 void* optarg ; 
 scalar_t__ optind ; 
 void* path_mdconfig ; 
 void* setmode (void*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 scalar_t__ strtoumax (char const*,char**,int /*<<< orphan*/ ) ; 
 int unit ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	struct mtpt_info mi;		/* Mountpoint info. */
	intmax_t mdsize;
	char *mdconfig_arg, *newfs_arg,	/* Args to helper programs. */
	    *mount_arg;
	enum md_types mdtype;		/* The type of our memory disk. */
	bool have_mdtype, mlmac;
	bool detach, softdep, autounit, newfs;
	const char *mtpoint, *size_arg, *skel, *unitstr;
	char *p;
	int ch, idx;
	void *set;
	unsigned long ul;

	/* Misc. initialization. */
	(void)memset(&mi, '\0', sizeof(mi));
	detach = true;
	softdep = true;
	autounit = false;
	mlmac = false;
	newfs = true;
	have_mdtype = false;
	skel = NULL;
	mdtype = MD_SWAP;
	mdname = MD_NAME;
	mdnamelen = strlen(mdname);
	mdsize = 0;
	/*
	 * Can't set these to NULL.  They may be passed to the
	 * respective programs without modification.  I.e., we may not
	 * receive any command-line options which will caused them to
	 * be modified.
	 */
	mdconfig_arg = strdup("");
	newfs_arg = strdup("");
	mount_arg = strdup("");
	size_arg = NULL;

	/* If we were started as mount_mfs or mfs, imply -C. */
	if (strcmp(getprogname(), "mount_mfs") == 0 ||
	    strcmp(getprogname(), "mfs") == 0) {
		/* Make compatibility assumptions. */
		mi.mi_mode = 01777;
		mi.mi_have_mode = true;
	}

	while ((ch = getopt(argc, argv,
	    "a:b:Cc:Dd:E:e:F:f:hi:k:LlMm:NnO:o:Pp:Ss:tT:Uv:w:X")) != -1)
		switch (ch) {
		case 'a':
			argappend(&newfs_arg, "-a %s", optarg);
			break;
		case 'b':
			argappend(&newfs_arg, "-b %s", optarg);
			break;
		case 'C':
			/* Ignored for compatibility. */
			break;
		case 'c':
			argappend(&newfs_arg, "-c %s", optarg);
			break;
		case 'D':
			detach = false;
			break;
		case 'd':
			argappend(&newfs_arg, "-d %s", optarg);
			break;
		case 'E':
			path_mdconfig = optarg;
			break;
		case 'e':
			argappend(&newfs_arg, "-e %s", optarg);
			break;
		case 'F':
			if (have_mdtype)
				usage();
			mdtype = MD_VNODE;
			have_mdtype = true;
			argappend(&mdconfig_arg, "-f %s", optarg);
			break;
		case 'f':
			argappend(&newfs_arg, "-f %s", optarg);
			break;
		case 'h':
			usage();
			break;
		case 'i':
			argappend(&newfs_arg, "-i %s", optarg);
			break;
		case 'k':
			skel = optarg;
			break;
		case 'L':
			loudsubs = true;
			break;
		case 'l':
			mlmac = true;
			argappend(&newfs_arg, "-l");
			break;
		case 'M':
			if (have_mdtype)
				usage();
			mdtype = MD_MALLOC;
			have_mdtype = true;
			argappend(&mdconfig_arg, "-o reserve");
			break;
		case 'm':
			argappend(&newfs_arg, "-m %s", optarg);
			break;
		case 'N':
			norun = true;
			break;
		case 'n':
			argappend(&newfs_arg, "-n");
			break;
		case 'O':
			argappend(&newfs_arg, "-o %s", optarg);
			break;
		case 'o':
			argappend(&mount_arg, "-o %s", optarg);
			break;
		case 'P':
			newfs = false;
			break;
		case 'p':
			if ((set = setmode(optarg)) == NULL)
				usage();
			mi.mi_mode = getmode(set, S_IRWXU | S_IRWXG | S_IRWXO);
			mi.mi_have_mode = true;
			mi.mi_forced_pw = true;
			free(set);
			break;
		case 'S':
			softdep = false;
			break;
		case 's':
			size_arg = optarg;
			break;
		case 't':
			argappend(&newfs_arg, "-t");
			break;
		case 'T':
			argappend(&mount_arg, "-t %s", optarg);
			break;
		case 'U':
			softdep = true;
			break;
		case 'v':
			argappend(&newfs_arg, "-O %s", optarg);
			break;
		case 'w':
			extract_ugid(optarg, &mi);
			mi.mi_forced_pw = true;
			break;
		case 'X':
			debug = true;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (argc < 2)
		usage();

	/*
	 * Historically our size arg was passed directly to mdconfig, which
	 * treats a number without a suffix as a count of 512-byte sectors;
	 * tmpfs would treat it as a count of bytes.  To get predictable
	 * behavior for 'auto' we document that the size always uses mdconfig
	 * rules.  To make that work, decode the size here so it can be passed
	 * to either tmpfs or mdconfig as a count of bytes.
	 */
	if (size_arg != NULL) {
		mdsize = (intmax_t)strtoumax(size_arg, &p, 0);
		if (p == size_arg || (p[0] != 0 && p[1] != 0) || mdsize < 0)
			errx(1, "invalid size '%s'", size_arg);
		switch (*p) {
		case 'p':
		case 'P':
			mdsize *= 1024;
		case 't':
		case 'T':
			mdsize *= 1024;
		case 'g':
		case 'G':
			mdsize *= 1024;
		case 'm':
		case 'M':
			mdsize *= 1024;
		case 'k':
		case 'K':
			mdsize *= 1024;
		case 'b':
		case 'B':
			break;
		case '\0':
			mdsize *= 512;
			break;
		default:
			errx(1, "invalid size suffix on '%s'", size_arg);
		}
	}

	/*
	 * Based on the command line 'md-device' either mount a tmpfs filesystem
	 * or configure the md device then format and mount a filesystem on it.
	 * If the device is 'auto' use tmpfs if it is available and there is no
	 * request for multilabel MAC (which tmpfs does not support).
	 */
	unitstr = argv[0];
	mtpoint = argv[1];

	if (strcmp(unitstr, "auto") == 0) {
		if (mlmac)
			idx = -1; /* Must use md for mlmac. */
		else if ((idx = modfind("tmpfs")) == -1)
			idx = kldload("tmpfs");
		if (idx == -1)
			unitstr = "md";
		else
			unitstr = "tmpfs";
	}

	if (strcmp(unitstr, "tmpfs") == 0) {
		if (size_arg != NULL && mdsize != 0)
			argappend(&mount_arg, "-o size=%jd", mdsize);
		do_mount_tmpfs(mount_arg, mtpoint); 
	} else {
		if (size_arg != NULL)
			argappend(&mdconfig_arg, "-s %jdB", mdsize);
		if (strncmp(unitstr, "/dev/", 5) == 0)
			unitstr += 5;
		if (strncmp(unitstr, mdname, mdnamelen) == 0)
			unitstr += mdnamelen;
		if (!isdigit(*unitstr)) {
			autounit = true;
			unit = -1;
			mdsuffix = unitstr;
		} else {
			ul = strtoul(unitstr, &p, 10);
			if (ul == ULONG_MAX)
				errx(1, "bad device unit: %s", unitstr);
			unit = ul;
			mdsuffix = p;	/* can be empty */
		}
	
		if (!have_mdtype)
			mdtype = MD_SWAP;
		if (softdep)
			argappend(&newfs_arg, "-U");
		if (mdtype != MD_VNODE && !newfs)
			errx(1, "-P requires a vnode-backed disk");
	
		/* Do the work. */
		if (detach && !autounit)
			do_mdconfig_detach();
		if (autounit)
			do_mdconfig_attach_au(mdconfig_arg, mdtype);
		else
			do_mdconfig_attach(mdconfig_arg, mdtype);
		if (newfs)
			do_newfs(newfs_arg);
		do_mount_md(mount_arg, mtpoint);
	}

	do_mtptsetup(mtpoint, &mi);
	if (skel != NULL)
		do_copy(mtpoint, skel);

	return (0);
}