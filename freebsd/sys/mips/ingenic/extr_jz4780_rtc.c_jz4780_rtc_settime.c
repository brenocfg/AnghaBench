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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct jz4780_rtc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_RTSR ; 
 struct jz4780_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int jz4780_rtc_write (struct jz4780_rtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_rtc_settime(device_t dev, struct timespec *ts)
{
	struct jz4780_rtc_softc *sc;

	sc = device_get_softc(dev);
	return jz4780_rtc_write(sc, JZ_RTSR, ts->tv_sec);
}