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
struct tty {int /*<<< orphan*/  t_dev; } ;
struct ptsstat {int /*<<< orphan*/  devname; int /*<<< orphan*/  dev; void* fs_typedep; } ;
struct filestat {int /*<<< orphan*/  devname; int /*<<< orphan*/  dev; void* fs_typedep; } ;
typedef  struct ptsstat kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  assert (struct ptsstat*) ; 
 int /*<<< orphan*/  bzero (struct ptsstat*,int) ; 
 int /*<<< orphan*/  dev2udev (struct ptsstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdevtoname (struct ptsstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_read_all (struct ptsstat*,unsigned long,struct tty*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

__attribute__((used)) static int
procstat_get_pts_info_kvm(kvm_t *kd, struct filestat *fst,
    struct ptsstat *pts, char *errbuf)
{
	struct tty tty;
	void *ttyp;

	assert(kd);
	assert(pts);
	assert(fst);
	bzero(pts, sizeof(*pts));
	ttyp = fst->fs_typedep;
	if (ttyp == NULL)
		goto fail;
	if (!kvm_read_all(kd, (unsigned long)ttyp, &tty, sizeof(struct tty))) {
		warnx("can't read tty at %p", (void *)ttyp);
		goto fail;
	}
	pts->dev = dev2udev(kd, tty.t_dev);
	(void)kdevtoname(kd, tty.t_dev, pts->devname);
	return (0);

fail:
	if (errbuf != NULL)
		snprintf(errbuf, _POSIX2_LINE_MAX, "error");
	return (1);
}