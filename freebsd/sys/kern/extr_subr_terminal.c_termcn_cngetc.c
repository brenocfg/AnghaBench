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
struct terminal {TYPE_1__* tm_class; } ;
struct consdev {struct terminal* cn_arg; } ;
struct TYPE_2__ {int (* tc_cngetc ) (struct terminal*) ;} ;

/* Variables and functions */
 int stub1 (struct terminal*) ; 

__attribute__((used)) static int
termcn_cngetc(struct consdev *cp)
{
	struct terminal *tm = cp->cn_arg;

	return (tm->tm_class->tc_cngetc(tm));
}