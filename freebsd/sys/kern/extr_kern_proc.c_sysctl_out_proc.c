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
struct sysctl_req {int /*<<< orphan*/ * oldptr; } ;
struct sbuf {int dummy; } ;
struct proc {int dummy; } ;
struct kinfo_proc {int dummy; } ;
typedef  int /*<<< orphan*/  ki ;

/* Variables and functions */
 int /*<<< orphan*/  SBUF_INCLUDENUL ; 
 int SYSCTL_OUT (struct sysctl_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_proc_out (struct proc*,struct sbuf*,int) ; 
 int /*<<< orphan*/  kern_proc_out_size (struct proc*,int) ; 
 int /*<<< orphan*/  sbuf_clear_flags (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new_for_sysctl (struct sbuf*,char*,int,struct sysctl_req*) ; 

__attribute__((used)) static int
sysctl_out_proc(struct proc *p, struct sysctl_req *req, int flags)
{
	struct sbuf sb;
	struct kinfo_proc ki;
	int error, error2;

	if (req->oldptr == NULL)
		return (SYSCTL_OUT(req, 0, kern_proc_out_size(p, flags)));

	sbuf_new_for_sysctl(&sb, (char *)&ki, sizeof(ki), req);
	sbuf_clear_flags(&sb, SBUF_INCLUDENUL);
	error = kern_proc_out(p, &sb, flags);
	error2 = sbuf_finish(&sb);
	sbuf_delete(&sb);
	if (error != 0)
		return (error);
	else if (error2 != 0)
		return (error2);
	return (0);
}