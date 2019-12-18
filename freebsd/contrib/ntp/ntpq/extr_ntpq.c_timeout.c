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
struct parse {scalar_t__ nargs; TYPE_1__* argval; } ;
struct TYPE_4__ {int tv_sec; int tv_usec; } ;
struct TYPE_3__ {int uval; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__ tvout ; 

__attribute__((used)) static void
timeout(
	struct parse *pcmd,
	FILE *fp
	)
{
	int val;

	if (pcmd->nargs == 0) {
		val = (int)tvout.tv_sec * 1000 + tvout.tv_usec / 1000;
		(void) fprintf(fp, "primary timeout %d ms\n", val);
	} else {
		tvout.tv_sec = pcmd->argval[0].uval / 1000;
		tvout.tv_usec = (pcmd->argval[0].uval - ((long)tvout.tv_sec * 1000))
			* 1000;
	}
}