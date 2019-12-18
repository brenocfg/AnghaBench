#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sun_disklabel {int sl_ntracks; int sl_nsectors; TYPE_1__* sl_part; int /*<<< orphan*/  sl_magic; } ;
struct gctl_req {int dummy; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  boot ;
struct TYPE_2__ {scalar_t__ sdkp_nsectors; int sdkp_cyloffset; } ;

/* Variables and functions */
 scalar_t__ Bflag ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SUN_BOOTSIZE ; 
 int /*<<< orphan*/  SUN_DKMAGIC ; 
 int SUN_NPART ; 
 int SUN_SIZE ; 
 char* _PATH_DEV ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ check_label (struct sun_disklabel*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_free (struct gctl_req*) ; 
 struct gctl_req* gctl_get_handle () ; 
 char* gctl_issue (struct gctl_req*) ; 
 int /*<<< orphan*/  gctl_ro_param (struct gctl_req*,char*,int,char const*) ; 
 scalar_t__ lseek (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nflag ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_label (struct sun_disklabel*,char const*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  sunlabel_enc (char*,struct sun_disklabel*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
write_label(struct sun_disklabel *sl, const char *disk, const char *bootpath)
{
	char path[MAXPATHLEN];
	char boot[SUN_BOOTSIZE];
	char buf[SUN_SIZE];
	const char *errstr;
	off_t off;
	int bfd;
	int fd;
	int i;
	struct gctl_req *grq;

	sl->sl_magic = SUN_DKMAGIC;

	if (check_label(sl) != 0)
		errx(1, "invalid label");

	bzero(buf, sizeof(buf));
	sunlabel_enc(buf, sl);

	if (nflag) {
		print_label(sl, disk, stdout);
		return;
	}
	if (Bflag) {
		if ((bfd = open(bootpath, O_RDONLY)) < 0)
			err(1, "open %s", bootpath);
		i = read(bfd, boot, sizeof(boot));
		if (i < 0)
			err(1, "read");
		else if (i != sizeof (boot))
			errx(1, "read wrong size boot code (%d)", i);
		close(bfd);
	}
	snprintf(path, sizeof(path), "%s%s", _PATH_DEV, disk);
	fd = open(path, O_RDWR);
	if (fd < 0) {
		grq = gctl_get_handle();
		gctl_ro_param(grq, "verb", -1, "write label");
		gctl_ro_param(grq, "class", -1, "SUN");
		gctl_ro_param(grq, "geom", -1, disk);
		gctl_ro_param(grq, "label", sizeof buf, buf);
		errstr = gctl_issue(grq);
		if (errstr != NULL)
			errx(1, "%s", errstr);
		gctl_free(grq);
		if (Bflag) {
			grq = gctl_get_handle();
			gctl_ro_param(grq, "verb", -1, "write bootcode");
			gctl_ro_param(grq, "class", -1, "SUN");
			gctl_ro_param(grq, "geom", -1, disk);
			gctl_ro_param(grq, "bootcode", sizeof boot, boot);
			errstr = gctl_issue(grq);
			if (errstr != NULL)
				errx(1, "%s", errstr);
			gctl_free(grq);
		}
	} else {
		if (lseek(fd, 0, SEEK_SET) < 0)
			err(1, "lseek");
		if (write(fd, buf, sizeof(buf)) != sizeof(buf))
			err (1, "write");
		if (Bflag) {
			for (i = 0; i < SUN_NPART; i++) {
				if (sl->sl_part[i].sdkp_nsectors == 0)
					continue;
				off = sl->sl_part[i].sdkp_cyloffset *
				    sl->sl_ntracks * sl->sl_nsectors * 512;
				/*
				 * Ignore first SUN_SIZE bytes of boot code to
				 * avoid overwriting the label.
				 */
				if (lseek(fd, off + SUN_SIZE, SEEK_SET) < 0)
					err(1, "lseek");
				if (write(fd, boot + SUN_SIZE,
				    sizeof(boot) - SUN_SIZE) !=
				    sizeof(boot) - SUN_SIZE)
					err(1, "write");
			}
		}
		close(fd);
	}
	exit(0);
}