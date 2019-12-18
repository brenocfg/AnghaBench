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
struct TYPE_2__ {double count; int /*<<< orphan*/  last; int /*<<< orphan*/  first; } ;
typedef  TYPE_1__ mru ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  LFPTOD (int /*<<< orphan*/ *,double) ; 
 scalar_t__ L_ISEQU (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ L_ISGEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L_SUB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qcmp_mru_avgint(
	const void *v1,
	const void *v2
	)
{
	const mru * const *	ppm1 = v1;
	const mru * const *	ppm2 = v2;
	const mru *		pm1;
	const mru *		pm2;
	l_fp			interval;
	double			avg1;
	double			avg2;

	pm1 = *ppm1;
	pm2 = *ppm2;

	interval = pm1->last;
	L_SUB(&interval, &pm1->first);
	LFPTOD(&interval, avg1);
	avg1 /= pm1->count;

	interval = pm2->last;
	L_SUB(&interval, &pm2->first);
	LFPTOD(&interval, avg2);
	avg2 /= pm2->count;

	if (avg1 < avg2)
		return -1;
	else if (avg1 > avg2)
		return 1;

	/* secondary sort on lstint - rarely tested */
	if (L_ISEQU(&pm1->last, &pm2->last))
		return 0;
	else if (L_ISGEQ(&pm1->last, &pm2->last))
		return -1;
	else
		return 1;
}