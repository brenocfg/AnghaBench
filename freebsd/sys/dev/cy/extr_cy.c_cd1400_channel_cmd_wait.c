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
struct timeval {int tv_sec; long tv_usec; } ;
struct com_s {int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD1400_CCR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ cd_getreg (struct com_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 

__attribute__((used)) static void
cd1400_channel_cmd_wait(struct com_s *com)
{
	struct timeval	start;
	struct timeval	tv;
	long		usec;

	if (cd_getreg(com, CD1400_CCR) == 0)
		return;
	microtime(&start);
	for (;;) {
		if (cd_getreg(com, CD1400_CCR) == 0)
			return;
		microtime(&tv);
		usec = 1000000 * (tv.tv_sec - start.tv_sec) +
		    tv.tv_usec - start.tv_usec;
		if (usec >= 5000) {
			log(LOG_ERR,
			    "cy%d: channel command timeout (%ld usec)\n",
			    com->unit, usec);
			return;
		}
	}
}