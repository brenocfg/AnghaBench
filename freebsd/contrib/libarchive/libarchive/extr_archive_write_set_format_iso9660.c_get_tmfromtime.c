#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  __time64_t ;

/* Variables and functions */
 int /*<<< orphan*/  _localtime64_s (struct tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  memcpy (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tzset () ; 

__attribute__((used)) static void
get_tmfromtime(struct tm *tm, time_t *t)
{
#if HAVE_LOCALTIME_R
	tzset();
	localtime_r(t, tm);
#elif HAVE__LOCALTIME64_S
	__time64_t tmp_t = (__time64_t) *t; //time_t may be shorter than 64 bits
	_localtime64_s(tm, &tmp_t);
#else
	memcpy(tm, localtime(t), sizeof(*tm));
#endif
}