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
struct tm {int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  errno ; 
 struct tm* gmtime_r (int /*<<< orphan*/  const*,struct tm*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

struct tm *git_gmtime_r(const time_t *timep, struct tm *result)
{
	struct tm *ret;

	memset(result, 0, sizeof(*result));
	ret = gmtime_r(timep, result);

	/*
	 * Rather than NULL, FreeBSD gmtime simply leaves the "struct tm"
	 * untouched when it encounters overflow. Since "mday" cannot otherwise
	 * be zero, we can test this very quickly.
	 */
	if (ret && !ret->tm_mday) {
		ret = NULL;
		errno = EOVERFLOW;
	}

	return ret;
}