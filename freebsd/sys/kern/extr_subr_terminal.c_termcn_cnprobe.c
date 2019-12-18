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
struct terminal {TYPE_1__* tm_class; struct consdev* consdev; } ;
struct consdev {int /*<<< orphan*/  cn_pri; struct terminal* cn_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc_cnprobe ) (struct terminal*,struct consdev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CN_DEAD ; 
 int /*<<< orphan*/  stub1 (struct terminal*,struct consdev*) ; 
 int /*<<< orphan*/  terminal_init (struct terminal*) ; 

__attribute__((used)) static void
termcn_cnprobe(struct consdev *cp)
{
	struct terminal *tm = cp->cn_arg;

	if (tm == NULL) {
		cp->cn_pri = CN_DEAD;
		return;
	}

	tm->consdev = cp;
	terminal_init(tm);

	tm->tm_class->tc_cnprobe(tm, cp);
}