#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_3__ {int hdr_cur_offs; unsigned long hdr_overflows; unsigned long hdr_count; int /*<<< orphan*/  hdr_version; int /*<<< orphan*/  hdr_buf_size; } ;
typedef  TYPE_1__ pfm_default_smpl_hdr_t ;
struct TYPE_4__ {int /*<<< orphan*/  buf_size; } ;
typedef  TYPE_2__ pfm_default_smpl_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  PFM_DEFAULT_SMPL_VERSION ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 

__attribute__((used)) static int
default_init(struct task_struct *task, void *buf, unsigned int flags, int cpu, void *data)
{
	pfm_default_smpl_hdr_t *hdr;
	pfm_default_smpl_arg_t *arg = (pfm_default_smpl_arg_t *)data;

	hdr = (pfm_default_smpl_hdr_t *)buf;

	hdr->hdr_version      = PFM_DEFAULT_SMPL_VERSION;
	hdr->hdr_buf_size     = arg->buf_size;
	hdr->hdr_cur_offs     = sizeof(*hdr);
	hdr->hdr_overflows    = 0UL;
	hdr->hdr_count        = 0UL;

	DPRINT(("[%d] buffer=%p buf_size=%lu hdr_size=%lu hdr_version=%u cur_offs=%lu\n",
		task_pid_nr(task),
		buf,
		hdr->hdr_buf_size,
		sizeof(*hdr),
		hdr->hdr_version,
		hdr->hdr_cur_offs));

	return 0;
}