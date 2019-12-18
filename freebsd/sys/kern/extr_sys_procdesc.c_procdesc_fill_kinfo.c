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
struct procdesc {int /*<<< orphan*/  pd_pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  kf_pid; } ;
struct TYPE_4__ {TYPE_1__ kf_proc; } ;
struct kinfo_file {TYPE_2__ kf_un; int /*<<< orphan*/  kf_type; } ;
struct filedesc {int dummy; } ;
struct file {struct procdesc* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KF_TYPE_PROCDESC ; 

__attribute__((used)) static int
procdesc_fill_kinfo(struct file *fp, struct kinfo_file *kif,
    struct filedesc *fdp)
{
	struct procdesc *pdp;

	kif->kf_type = KF_TYPE_PROCDESC;
	pdp = fp->f_data;
	kif->kf_un.kf_proc.kf_pid = pdp->pd_pid;
	return (0);
}