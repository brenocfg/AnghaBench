#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int sched_nr; } ;
struct dn_schk {TYPE_4__ sch; struct dn_fsk* fs; int /*<<< orphan*/  profile; TYPE_4__ link; } ;
struct TYPE_7__ {int fs_nr; } ;
struct dn_fsk {TYPE_3__ fs; } ;
struct copy_args {scalar_t__ type; int flags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; TYPE_2__* extra; } ;
struct TYPE_5__ {int len; } ;
struct TYPE_6__ {int* r; TYPE_1__ o; } ;

/* Variables and functions */
 int DNHT_SCAN_END ; 
 int DN_C_FLOW ; 
 int DN_C_LINK ; 
 int DN_C_SCH ; 
 scalar_t__ DN_FS ; 
 scalar_t__ DN_LINK ; 
 int DN_MAX_ID ; 
 scalar_t__ DN_SCH ; 
 scalar_t__ copy_flowset (struct copy_args*,struct dn_fsk*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_fsk_list (struct copy_args*,struct dn_schk*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,char*,int) ; 
 scalar_t__ copy_profile (struct copy_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_q (struct copy_args*,struct dn_fsk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_si (struct copy_args*,struct dn_schk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
copy_data_helper(void *_o, void *_arg)
{
	struct copy_args *a = _arg;
	uint32_t *r = a->extra->r; /* start of first range */
	uint32_t *lim;	/* first invalid pointer */
	int n;

	lim = (uint32_t *)((char *)(a->extra) + a->extra->o.len);

	if (a->type == DN_LINK || a->type == DN_SCH) {
		/* pipe|sched show, we receive a dn_schk */
		struct dn_schk *s = _o;

		n = s->sch.sched_nr;
		if (a->type == DN_SCH && n >= DN_MAX_ID)
			return 0;	/* not a scheduler */
		if (a->type == DN_LINK && n <= DN_MAX_ID)
		    return 0;	/* not a pipe */

		/* see if the object is within one of our ranges */
		for (;r < lim; r += 2) {
			if (n < r[0] || n > r[1])
				continue;
			/* Found a valid entry, copy and we are done */
			if (a->flags & DN_C_LINK) {
				if (copy_obj(a->start, a->end,
				    &s->link, "link", n))
					return DNHT_SCAN_END;
				if (copy_profile(a, s->profile))
					return DNHT_SCAN_END;
				if (copy_flowset(a, s->fs, 0))
					return DNHT_SCAN_END;
			}
			if (a->flags & DN_C_SCH) {
				if (copy_obj(a->start, a->end,
				    &s->sch, "sched", n))
					return DNHT_SCAN_END;
				/* list all attached flowsets */
				if (copy_fsk_list(a, s, 0))
					return DNHT_SCAN_END;
			}
			if (a->flags & DN_C_FLOW)
				copy_si(a, s, 0);
			break;
		}
	} else if (a->type == DN_FS) {
		/* queue show, skip internal flowsets */
		struct dn_fsk *fs = _o;

		n = fs->fs.fs_nr;
		if (n >= DN_MAX_ID)
			return 0;
		/* see if the object is within one of our ranges */
		for (;r < lim; r += 2) {
			if (n < r[0] || n > r[1])
				continue;
			if (copy_flowset(a, fs, 0))
				return DNHT_SCAN_END;
			copy_q(a, fs, 0);
			break; /* we are done */
		}
	}
	return 0;
}