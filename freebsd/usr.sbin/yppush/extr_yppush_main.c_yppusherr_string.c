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
#define  YPPUSH_NOHOST 131 
#define  YPPUSH_PMAP 130 
#define  YPPUSH_TIMEDOUT 129 
#define  YPPUSH_YPSERV 128 

__attribute__((used)) static const char *
yppusherr_string(int err)
{
	switch (err) {
	case YPPUSH_TIMEDOUT:
		return("transfer or callback timed out");
	case YPPUSH_YPSERV:
		return("failed to contact ypserv");
	case YPPUSH_NOHOST:
		return("no such host");
	case YPPUSH_PMAP:
		return("portmapper failure");
	default:
		return("unknown error code");
	}
}