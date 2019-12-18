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
struct knote {scalar_t__ kn_data; scalar_t__ kn_hook; } ;
struct audit_pipe {scalar_t__ ap_qlen; scalar_t__ ap_qoffset; scalar_t__ ap_qbyteslen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_ASSERT (struct audit_pipe*) ; 

__attribute__((used)) static int
audit_pipe_kqread(struct knote *kn, long hint)
{
	struct audit_pipe *ap;

	ap = (struct audit_pipe *)kn->kn_hook;
	AUDIT_PIPE_LOCK_ASSERT(ap);

	if (ap->ap_qlen != 0) {
		kn->kn_data = ap->ap_qbyteslen - ap->ap_qoffset;
		return (1);
	} else {
		kn->kn_data = 0;
		return (0);
	}
}