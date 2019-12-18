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
typedef  int /*<<< orphan*/  tv ;
typedef  int /*<<< orphan*/  time_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_GetTimeOfDay (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct timeval*,int /*<<< orphan*/ ,int) ; 

time_t
time(time_t *tloc)
{
	struct timeval tv;

	memset(&tv, 0, sizeof(tv));
	EFI_GetTimeOfDay(&tv, NULL);

	if (tloc)
		*tloc = tv.tv_sec;
	return (tv.tv_sec);
}