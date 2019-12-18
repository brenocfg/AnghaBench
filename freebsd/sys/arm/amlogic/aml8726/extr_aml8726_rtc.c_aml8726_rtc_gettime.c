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
typedef  int /*<<< orphan*/  uint32_t ;
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct aml8726_rtc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RTC_LOCK (struct aml8726_rtc_softc*) ; 
 int /*<<< orphan*/  AML_RTC_TIME_SREG ; 
 int /*<<< orphan*/  AML_RTC_UNLOCK (struct aml8726_rtc_softc*) ; 
 int aml8726_rtc_sreg_read (struct aml8726_rtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aml8726_rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aml8726_rtc_gettime(device_t dev, struct timespec *ts)
{
	struct aml8726_rtc_softc *sc = device_get_softc(dev);
	uint32_t sec;
	int error;

	AML_RTC_LOCK(sc);

	error = aml8726_rtc_sreg_read(sc, AML_RTC_TIME_SREG, &sec);

	AML_RTC_UNLOCK(sc);

	ts->tv_sec = sec;
	ts->tv_nsec = 0;

	return (error);
}