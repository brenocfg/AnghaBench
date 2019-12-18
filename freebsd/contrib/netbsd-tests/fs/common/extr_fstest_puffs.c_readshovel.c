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
struct putter_hdr {int pth_framelen; } ;
struct puffstestargs {int pta_servfd; int pta_rumpfd; int /*<<< orphan*/ * pta_vn_toserv_ops; int /*<<< orphan*/ * pta_vfs_toserv_ops; } ;
struct puffs_req {size_t preq_optype; int /*<<< orphan*/  preq_opclass; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BUFSIZE ; 
 scalar_t__ PUFFSOP_OPCLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ PUFFSOP_VFS ; 
 scalar_t__ PUFFSOP_VN ; 
 size_t PUFFS_VFS_MAX ; 
 size_t PUFFS_VN_MAX ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int mayquit ; 
 int /*<<< orphan*/  rump_pub_lwproc_newlwp (int) ; 
 int rump_sys_read (int,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int xwrite (int,char*,int) ; 

__attribute__((used)) static void *
readshovel(void *arg)
{
	struct putter_hdr *phdr;
	struct puffs_req *preq;
	struct puffstestargs *args = arg;
	char buf[BUFSIZE];
	ssize_t n;
	int comfd, puffsfd;

	comfd = args->pta_servfd;
	puffsfd = args->pta_rumpfd;

	phdr = (void *)buf;
	preq = (void *)buf;

	rump_pub_lwproc_newlwp(1);

	for (;;) {
		n = rump_sys_read(puffsfd, buf, sizeof(*phdr));
		if (n <= 0) {
			fprintf(stderr, "readshovel r1 %zd / %d\n", n, errno);
			break;
		}

		assert(phdr->pth_framelen < BUFSIZE);
		n = rump_sys_read(puffsfd, buf+sizeof(*phdr), 
		    phdr->pth_framelen - sizeof(*phdr));
		if (n <= 0) {
			fprintf(stderr, "readshovel r2 %zd / %d\n", n, errno);
			break;
		}

		/* Analyze request */
		if (PUFFSOP_OPCLASS(preq->preq_opclass) == PUFFSOP_VFS) {
			assert(preq->preq_optype < PUFFS_VFS_MAX);
			args->pta_vfs_toserv_ops[preq->preq_optype]++;
		} else if (PUFFSOP_OPCLASS(preq->preq_opclass) == PUFFSOP_VN) {
			assert(preq->preq_optype < PUFFS_VN_MAX);
			args->pta_vn_toserv_ops[preq->preq_optype]++;
		}

		n = phdr->pth_framelen;
		if (xwrite(comfd, buf, n) != n) {
			fprintf(stderr, "readshovel write %zd / %d\n", n, errno);
			break;
		}
	}

	if (n != 0 && mayquit == false)
		abort();
	return NULL;
}