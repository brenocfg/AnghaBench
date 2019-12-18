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
struct asmc_softc {int /*<<< orphan*/  sms_rest_z; int /*<<< orphan*/  sms_rest_y; int /*<<< orphan*/  sms_rest_x; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASMC_KEY_SMS_X ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_Y ; 
 int /*<<< orphan*/  ASMC_KEY_SMS_Z ; 
 int /*<<< orphan*/  asmc_sms_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct asmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
asmc_sms_calibrate(device_t dev)
{
	struct asmc_softc *sc = device_get_softc(dev);

	asmc_sms_read(dev, ASMC_KEY_SMS_X, &sc->sms_rest_x);
	asmc_sms_read(dev, ASMC_KEY_SMS_Y, &sc->sms_rest_y);
	asmc_sms_read(dev, ASMC_KEY_SMS_Z, &sc->sms_rest_z);
}