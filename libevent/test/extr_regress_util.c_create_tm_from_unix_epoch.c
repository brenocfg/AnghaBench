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
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 struct tm* gmtime (scalar_t__ const*) ; 
 int /*<<< orphan*/  gmtime_r (scalar_t__ const*,struct tm*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
create_tm_from_unix_epoch(struct tm *cur_p, const time_t t)
{
#ifdef _WIN32
	struct tm *tmp = gmtime(&t);
	if (!tmp) {
		fprintf(stderr, "gmtime: %s (%i)", strerror(errno), (int)t);
		exit(1);
	}
	*cur_p = *tmp;
#else
	gmtime_r(&t, cur_p);
#endif
}