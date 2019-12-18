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

/* Variables and functions */
 char* asctime_r (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/  const* const,struct tm*) ; 

char *
ctime_r(const time_t *const timep, char *buf)
{
	struct tm	mytm;

	return asctime_r(localtime_r(timep, &mytm), buf);
}