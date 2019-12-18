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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int pptptime_t ;

/* Variables and functions */
 int PPTP_TIME_SCALE ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 

__attribute__((used)) static pptptime_t
ng_pptpgre_time(void)
{
	struct timeval tv;
	pptptime_t t;

	microuptime(&tv);
	t = (pptptime_t)tv.tv_sec * PPTP_TIME_SCALE;
	t += tv.tv_usec / (1000000 / PPTP_TIME_SCALE);
	return(t);
}