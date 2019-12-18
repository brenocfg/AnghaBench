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
struct pipestat {uintptr_t addr; uintptr_t peer; int /*<<< orphan*/  buffer_cnt; void* fs_typedep; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnt; } ;
struct pipe {TYPE_1__ pipe_buffer; scalar_t__ pipe_peer; } ;
struct filestat {uintptr_t addr; uintptr_t peer; int /*<<< orphan*/  buffer_cnt; void* fs_typedep; } ;
typedef  struct pipestat kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  assert (struct pipestat*) ; 
 int /*<<< orphan*/  bzero (struct pipestat*,int) ; 
 int /*<<< orphan*/  kvm_read_all (struct pipestat*,unsigned long,struct pipe*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

__attribute__((used)) static int
procstat_get_pipe_info_kvm(kvm_t *kd, struct filestat *fst,
    struct pipestat *ps, char *errbuf)
{
	struct pipe pi;
	void *pipep;

	assert(kd);
	assert(ps);
	assert(fst);
	bzero(ps, sizeof(*ps));
	pipep = fst->fs_typedep;
	if (pipep == NULL)
		goto fail;
	if (!kvm_read_all(kd, (unsigned long)pipep, &pi, sizeof(struct pipe))) {
		warnx("can't read pipe at %p", (void *)pipep);
		goto fail;
	}
	ps->addr = (uintptr_t)pipep;
	ps->peer = (uintptr_t)pi.pipe_peer;
	ps->buffer_cnt = pi.pipe_buffer.cnt;
	return (0);

fail:
	if (errbuf != NULL)
		snprintf(errbuf, _POSIX2_LINE_MAX, "error");
	return (1);
}