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
struct TYPE_5__ {int subtype; } ;
struct TYPE_6__ {scalar_t__ sched_nr; TYPE_2__ oid; } ;
struct dn_schk {TYPE_3__ sch; } ;
struct TYPE_4__ {scalar_t__ fs_nr; } ;
struct dn_fsk {TYPE_1__ fs; } ;
struct copy_args {scalar_t__ type; } ;

/* Variables and functions */
 int DNHT_SCAN_END ; 
 scalar_t__ DN_COMPAT_PIPE ; 
 scalar_t__ DN_COMPAT_QUEUE ; 
 scalar_t__ DN_MAX_ID ; 
 scalar_t__ dn_compat_copy_pipe (struct copy_args*,void*) ; 
 scalar_t__ dn_compat_copy_queue (struct copy_args*,void*) ; 

int
copy_data_helper_compat(void *_o, void *_arg)
{
	struct copy_args *a = _arg;

	if (a->type == DN_COMPAT_PIPE) {
		struct dn_schk *s = _o;
		if (s->sch.oid.subtype != 1 || s->sch.sched_nr <= DN_MAX_ID) {
			return 0;	/* not old type */
		}
		/* copy pipe parameters, and if instance exists, copy
		 * other parameters and eventually queues.
		 */
		if(dn_compat_copy_pipe(a, _o))
			return DNHT_SCAN_END;
	} else if (a->type == DN_COMPAT_QUEUE) {
		struct dn_fsk *fs = _o;
		if (fs->fs.fs_nr >= DN_MAX_ID)
			return 0;
		if (dn_compat_copy_queue(a, _o))
			return DNHT_SCAN_END;
	}
	return 0;
}