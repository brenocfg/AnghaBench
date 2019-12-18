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
struct TYPE_4__ {int hi; int lo; } ;
struct TYPE_5__ {scalar_t__ q_s; TYPE_1__ D_s; } ;
typedef  TYPE_2__ vint64 ;
typedef  int u_int32 ;
typedef  scalar_t__ time_t ;
struct tm {scalar_t__ tm_year; } ;
typedef  scalar_t__ int64 ;
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 scalar_t__ MAXFOLD ; 
 scalar_t__ MINFOLD ; 
 int /*<<< orphan*/  M_ADD (int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ M_ISNEG (int,int) ; 
 int /*<<< orphan*/  M_SUB (int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SOLAR_CYCLE_SECS ; 
 scalar_t__ SOLAR_CYCLE_YEARS ; 
 struct tm* gmtime (scalar_t__*) ; 
 struct tm* localtime (scalar_t__*) ; 
 struct tm* stub1 (scalar_t__*) ; 

__attribute__((used)) static struct tm *
get_struct_tm(
	const vint64 *stamp,
	int	      local)
{
	struct tm *tm	 = NULL;
	int32	   folds = 0;
	time_t	   ts;

#ifdef HAVE_INT64

	int64 tl;
	ts = tl = stamp->q_s;

	/*
	 * If there is chance of truncation, try to fix it. Let the
	 * compiler find out if this can happen at all.
	 */
	while (ts != tl) { /* truncation? */
		if (tl < 0) {
			if (--folds < MINFOLD)
				return NULL;
			tl += SOLAR_CYCLE_SECS;
		} else {
			if (++folds > MAXFOLD)
				return NULL;
			tl -= SOLAR_CYCLE_SECS;
		}
		ts = tl; /* next try... */
	}
#else

	/*
	 * since we do not have 64-bit scalars, it's not likely we have
	 * 64-bit time_t. Assume 32 bits and properly reduce the value.
	 */
	u_int32 hi, lo;

	hi = stamp->D_s.hi;
	lo = stamp->D_s.lo;

	while ((hi && ~hi) || ((hi ^ lo) & 0x80000000u)) {
		if (M_ISNEG(hi, lo)) {
			if (--folds < MINFOLD)
				return NULL;
			M_ADD(hi, lo, 0, SOLAR_CYCLE_SECS);
		} else {
			if (++folds > MAXFOLD)
				return NULL;
			M_SUB(hi, lo, 0, SOLAR_CYCLE_SECS);
		}
	}
	ts = (int32)lo;

#endif

	/*
	 * 'ts' should be a suitable value by now. Just go ahead, but
	 * with care:
	 *
	 * There are some pathological implementations of 'gmtime()'
	 * and 'localtime()' out there. No matter if we have 32-bit or
	 * 64-bit 'time_t', try to fix this by solar cycle warping
	 * again...
	 *
	 * At least the MSDN says that the (Microsoft) Windoze
	 * versions of 'gmtime()' and 'localtime()' will bark on time
	 * stamps < 0.
	 */
	while ((tm = (*(local ? localtime : gmtime))(&ts)) == NULL)
		if (ts < 0) {
			if (--folds < MINFOLD)
				return NULL;
			ts += SOLAR_CYCLE_SECS;
		} else if (ts >= (time_t)SOLAR_CYCLE_SECS) {
			if (++folds > MAXFOLD)
				return NULL;
			ts -= SOLAR_CYCLE_SECS;
		} else
			return NULL; /* That's truly pathological! */

	/* 'tm' surely not NULL here! */
	INSIST(tm != NULL);
	if (folds != 0) {
		tm->tm_year += folds * SOLAR_CYCLE_YEARS;
		if (tm->tm_year <= 0 || tm->tm_year >= 200)
			return NULL;	/* left warp range... can't help here! */
	}

	return tm;
}