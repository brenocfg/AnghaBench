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
struct asmc_softc {int sc_sms_intrtype; } ;
typedef  int /*<<< orphan*/  notify ;

/* Variables and functions */
#define  ASMC_SMS_INTFF 130 
#define  ASMC_SMS_INTHA 129 
#define  ASMC_SMS_INTSH 128 
 int /*<<< orphan*/  devctl_notify (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
asmc_sms_task(void *arg, int pending)
{
	struct asmc_softc *sc = (struct asmc_softc *)arg;
	char notify[16];
	int type;

	switch (sc->sc_sms_intrtype) {
	case ASMC_SMS_INTFF:
		type = 2;
		break;
	case ASMC_SMS_INTHA:
		type = 1;
		break;
	case ASMC_SMS_INTSH:
		type = 0;
		break;
	default:
		type = 255;
	}

	snprintf(notify, sizeof(notify), " notify=0x%x", type);
	devctl_notify("ACPI", "asmc", "SMS", notify);
}