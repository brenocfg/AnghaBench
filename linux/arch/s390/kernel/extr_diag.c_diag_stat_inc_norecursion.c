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
typedef  enum diag_stat_enum { ____Placeholder_diag_stat_enum } diag_stat_enum ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;
struct TYPE_3__ {int /*<<< orphan*/ * counter; } ;

/* Variables and functions */
 TYPE_2__* diag_map ; 
 TYPE_1__ diag_stat ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_s390_diagnose_norecursion (int /*<<< orphan*/ ) ; 

void diag_stat_inc_norecursion(enum diag_stat_enum nr)
{
	this_cpu_inc(diag_stat.counter[nr]);
	trace_s390_diagnose_norecursion(diag_map[nr].code);
}