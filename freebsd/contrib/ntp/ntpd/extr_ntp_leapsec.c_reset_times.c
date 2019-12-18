#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vint64 ;
struct TYPE_4__ {int /*<<< orphan*/  ebase; int /*<<< orphan*/  dtime; int /*<<< orphan*/  ttime; int /*<<< orphan*/  stime; } ;
struct TYPE_5__ {TYPE_1__ head; } ;
typedef  TYPE_2__ leap_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
reset_times(
	leap_table_t * pt)
{
	memset(&pt->head.ebase, 0xFF, sizeof(vint64));
	pt->head.stime = pt->head.ebase;
	pt->head.ttime = pt->head.ebase;
	pt->head.dtime = pt->head.ebase;
}