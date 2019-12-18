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

/* Variables and functions */
 unsigned long INT_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int failure_retry_rate ; 
 int foreground ; 
 char* pidfile ; 
 int set_retry_cnt ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int process_opts(void *context, int ch, char *optarg)
{
	unsigned long tmp;
	switch (ch) {
	case 0:
		pidfile = optarg;
		break;
	case 'f':
		foreground = 1;
		break;
	case 't':
		tmp = strtoul(optarg, NULL, 0);
		if (tmp >= INT_MAX) {
			syslog(LOG_ERR,
				"Invalid retry rate specified: %lu s\n",
				tmp);
		} else {
			failure_retry_rate = (int)tmp;
		}
		break;
	case 'r':
		tmp = strtoul(optarg, NULL, 0);
		if (tmp >= INT_MAX) {
			syslog(LOG_ERR,
				"Invalid retry count specified: %lu\n",
				tmp);
		} else {
			set_retry_cnt = (int)tmp;
		}
		break;
	default:
		return -1;
	}
	return 0;
}