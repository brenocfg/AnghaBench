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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct timeval {int dummy; } ;
struct TYPE_2__ {int cnt; int in; int out; int size; int /*<<< orphan*/ * buffer; } ;
struct pipe {int pipe_state; TYPE_1__ pipe_buffer; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_SUCCESS ; 
 int PIPE_DIRECTW ; 
 int /*<<< orphan*/  PIPE_MTX (struct pipe*) ; 
 int SMALL_PIPE_SIZE ; 
 int /*<<< orphan*/  VMFS_ANY_SPACE ; 
 int /*<<< orphan*/  VM_PROT_RW ; 
 int /*<<< orphan*/  amountpipekva ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_free_kmem (struct pipe*) ; 
 int /*<<< orphan*/  pipe_map ; 
 int /*<<< orphan*/  pipeallocfail ; 
 int /*<<< orphan*/  pipefragretry ; 
 int /*<<< orphan*/  piperesizefail ; 
 scalar_t__ ppsratecheck (struct timeval*,int*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int round_page (int) ; 
 int vm_map_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pipespace_new(struct pipe *cpipe, int size)
{
	caddr_t buffer;
	int error, cnt, firstseg;
	static int curfail = 0;
	static struct timeval lastfail;

	KASSERT(!mtx_owned(PIPE_MTX(cpipe)), ("pipespace: pipe mutex locked"));
	KASSERT(!(cpipe->pipe_state & PIPE_DIRECTW),
		("pipespace: resize of direct writes not allowed"));
retry:
	cnt = cpipe->pipe_buffer.cnt;
	if (cnt > size)
		size = cnt;

	size = round_page(size);
	buffer = (caddr_t) vm_map_min(pipe_map);

	error = vm_map_find(pipe_map, NULL, 0, (vm_offset_t *)&buffer, size, 0,
	    VMFS_ANY_SPACE, VM_PROT_RW, VM_PROT_RW, 0);
	if (error != KERN_SUCCESS) {
		if ((cpipe->pipe_buffer.buffer == NULL) &&
			(size > SMALL_PIPE_SIZE)) {
			size = SMALL_PIPE_SIZE;
			pipefragretry++;
			goto retry;
		}
		if (cpipe->pipe_buffer.buffer == NULL) {
			pipeallocfail++;
			if (ppsratecheck(&lastfail, &curfail, 1))
				printf("kern.ipc.maxpipekva exceeded; see tuning(7)\n");
		} else {
			piperesizefail++;
		}
		return (ENOMEM);
	}

	/* copy data, then free old resources if we're resizing */
	if (cnt > 0) {
		if (cpipe->pipe_buffer.in <= cpipe->pipe_buffer.out) {
			firstseg = cpipe->pipe_buffer.size - cpipe->pipe_buffer.out;
			bcopy(&cpipe->pipe_buffer.buffer[cpipe->pipe_buffer.out],
				buffer, firstseg);
			if ((cnt - firstseg) > 0)
				bcopy(cpipe->pipe_buffer.buffer, &buffer[firstseg],
					cpipe->pipe_buffer.in);
		} else {
			bcopy(&cpipe->pipe_buffer.buffer[cpipe->pipe_buffer.out],
				buffer, cnt);
		}
	}
	pipe_free_kmem(cpipe);
	cpipe->pipe_buffer.buffer = buffer;
	cpipe->pipe_buffer.size = size;
	cpipe->pipe_buffer.in = cnt;
	cpipe->pipe_buffer.out = 0;
	cpipe->pipe_buffer.cnt = cnt;
	atomic_add_long(&amountpipekva, cpipe->pipe_buffer.size);
	return (0);
}