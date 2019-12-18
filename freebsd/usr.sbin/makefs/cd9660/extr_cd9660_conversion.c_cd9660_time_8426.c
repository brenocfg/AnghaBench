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
typedef  int /*<<< orphan*/  temp ;
struct tm {scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; scalar_t__ tm_sec; scalar_t__ tm_min; } ;

/* Variables and functions */
 unsigned char cd9660_compute_gm_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 

void
cd9660_time_8426(unsigned char *buf, time_t tim)
{
	struct tm t;
	char temp[18];

	(void)localtime_r(&tim, &t);
	(void)snprintf(temp, sizeof(temp), "%04i%02i%02i%02i%02i%02i%02i",
		1900+(int)t.tm_year,
		(int)t.tm_mon+1,
		(int)t.tm_mday,
		(int)t.tm_hour,
		(int)t.tm_min,
		(int)t.tm_sec,
		0);
	(void)memcpy(buf, temp, 16);
	buf[16] = cd9660_compute_gm_offset(tim);
}