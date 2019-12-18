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
struct archive_string {int dummy; } ;
typedef  int /*<<< orphan*/  strtime ;

/* Variables and functions */
 int /*<<< orphan*/  _gmtime64_s (struct tm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_strncat (struct archive_string*,char*,size_t) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 struct tm* gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 size_t strftime (char*,int,char const*,struct tm*) ; 

__attribute__((used)) static void
xstrftime(struct archive_string *as, const char *fmt, time_t t)
{
/** like strftime(3) but for time_t objects */
	struct tm *rt;
#if defined(HAVE_GMTIME_R) || defined(HAVE__GMTIME64_S)
	struct tm timeHere;
#endif
	char strtime[100];
	size_t len;

#ifdef HAVE_GMTIME_R
	if ((rt = gmtime_r(&t, &timeHere)) == NULL)
		return;
#elif defined(HAVE__GMTIME64_S)
	_gmtime64_s(&timeHere, &t);
#else
	if ((rt = gmtime(&t)) == NULL)
		return;
#endif
	/* leave the hard yacker to our role model strftime() */
	len = strftime(strtime, sizeof(strtime)-1, fmt, rt);
	archive_strncat(as, strtime, len);
}