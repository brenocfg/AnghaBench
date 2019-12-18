#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ res_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ res; int /*<<< orphan*/  pri; int /*<<< orphan*/  lineno; } ;
typedef  TYPE_1__ collpri_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 scalar_t__ REFER ; 
 scalar_t__ RESOLVED ; 
 scalar_t__ UNKNOWN ; 
 TYPE_1__* get_pri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lineno ; 
 int /*<<< orphan*/  nextpri ; 
 int /*<<< orphan*/  numpri ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_pri(int32_t ref, int32_t v, res_t res)
{
	collpri_t	*pri;

	pri = get_pri(ref);

	if ((res == REFER) && ((v < 0) || (v >= numpri))) {
		INTERR;
	}

	/* Resolve self references */
	if ((res == REFER) && (ref == v)) {
		v = nextpri;
		res = RESOLVED;
	}

	if (pri->res != UNKNOWN) {
		warn("repeated item in order list (first on %d)",
		    pri->lineno);
		return;
	}
	pri->lineno = lineno;
	pri->pri = v;
	pri->res = res;
}