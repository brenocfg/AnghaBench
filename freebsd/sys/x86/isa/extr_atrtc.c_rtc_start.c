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
struct eventtimer {int dummy; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  atrtc_enable_intr () ; 
 int /*<<< orphan*/  atrtc_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ fls (int) ; 
 int /*<<< orphan*/  max (scalar_t__,int) ; 

__attribute__((used)) static int
rtc_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{

	atrtc_rate(max(fls(period + (period >> 1)) - 17, 1));
	atrtc_enable_intr();
	return (0);
}