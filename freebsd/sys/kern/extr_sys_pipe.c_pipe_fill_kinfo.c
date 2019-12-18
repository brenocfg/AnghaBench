#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cnt; } ;
struct pipe {TYPE_3__ pipe_buffer; scalar_t__ pipe_peer; } ;
struct TYPE_4__ {uintptr_t kf_pipe_addr; uintptr_t kf_pipe_peer; int /*<<< orphan*/  kf_pipe_buffer_cnt; } ;
struct TYPE_5__ {TYPE_1__ kf_pipe; } ;
struct kinfo_file {TYPE_2__ kf_un; int /*<<< orphan*/  kf_type; } ;
struct filedesc {int dummy; } ;
struct file {scalar_t__ f_type; struct pipe* f_data; } ;

/* Variables and functions */
 scalar_t__ DTYPE_FIFO ; 
 int /*<<< orphan*/  KF_TYPE_PIPE ; 
 int vn_fill_kinfo (struct file*,struct kinfo_file*,struct filedesc*) ; 

__attribute__((used)) static int
pipe_fill_kinfo(struct file *fp, struct kinfo_file *kif, struct filedesc *fdp)
{
	struct pipe *pi;

	if (fp->f_type == DTYPE_FIFO)
		return (vn_fill_kinfo(fp, kif, fdp));
	kif->kf_type = KF_TYPE_PIPE;
	pi = fp->f_data;
	kif->kf_un.kf_pipe.kf_pipe_addr = (uintptr_t)pi;
	kif->kf_un.kf_pipe.kf_pipe_peer = (uintptr_t)pi->pipe_peer;
	kif->kf_un.kf_pipe.kf_pipe_buffer_cnt = pi->pipe_buffer.cnt;
	return (0);
}