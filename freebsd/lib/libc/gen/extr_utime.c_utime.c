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
struct utimbuf {int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int utimes (char const*,struct timeval*) ; 

int
utime(const char *path, const struct utimbuf *times)
{
	struct timeval tv[2], *tvp;

	if (times) {
		tv[0].tv_sec = times->actime;
		tv[1].tv_sec = times->modtime;
		tv[0].tv_usec = tv[1].tv_usec = 0;
		tvp = tv;
	} else
		tvp = NULL;
	return (utimes(path, tvp));
}