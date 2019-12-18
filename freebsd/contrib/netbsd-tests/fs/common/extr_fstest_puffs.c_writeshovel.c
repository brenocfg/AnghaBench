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
typedef  int uint64_t ;
struct putter_hdr {int pth_framelen; } ;
struct puffstestargs {int pta_servfd; int pta_rumpfd; } ;
struct puffs_req {scalar_t__ preq_optype; scalar_t__ preq_rv; int /*<<< orphan*/  preq_opclass; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BUFSIZE ; 
 scalar_t__ PUFFSOP_OPCLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ PUFFSOP_VFS ; 
 scalar_t__ PUFFS_VFS_UNMOUNT ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int mayquit ; 
 int /*<<< orphan*/  rump_pub_lwproc_newlwp (int) ; 
 int rump_sys_write (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int xread (int,char*,size_t) ; 

__attribute__((used)) static void *
writeshovel(void *arg)
{
	struct puffstestargs *args = arg;
	struct putter_hdr *phdr;
	struct puffs_req *preq;
	char buf[BUFSIZE];
	size_t toread;
	ssize_t n;
	int comfd, puffsfd;

	rump_pub_lwproc_newlwp(1);

	comfd = args->pta_servfd;
	puffsfd = args->pta_rumpfd;

	phdr = (struct putter_hdr *)buf;
	preq = (void *)buf;

	for (;;) {
		uint64_t off;

		/*
		 * Need to write everything to the "kernel" in one chunk,
		 * so make sure we have it here.
		 */
		off = 0;
		toread = sizeof(struct putter_hdr);
		assert(toread < BUFSIZE);
		do {
			n = xread(comfd, buf+off, toread);
			if (n <= 0) {
				fprintf(stderr, "writeshovel read %zd / %d\n",
				    n, errno);
				goto out;
			}
			off += n;
			if (off >= sizeof(struct putter_hdr))
				toread = phdr->pth_framelen - off;
			else
				toread = off - sizeof(struct putter_hdr);
		} while (toread);

		if (__predict_false(
		    PUFFSOP_OPCLASS(preq->preq_opclass) == PUFFSOP_VFS
		    && preq->preq_optype == PUFFS_VFS_UNMOUNT)) {
			if (preq->preq_rv == 0)
				mayquit = true;
		}

		n = rump_sys_write(puffsfd, buf, phdr->pth_framelen);
		if ((size_t)n != phdr->pth_framelen) {
			fprintf(stderr, "writeshovel wr %zd / %d\n", n, errno);
			break;
		}
	}

 out:
	if (n != 0)
		abort();
	return NULL;
}