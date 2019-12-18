#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct TYPE_4__ {int Year; int Month; int Second; scalar_t__ Daylight; scalar_t__ TimeZone; scalar_t__ Nanosecond; scalar_t__ Minute; scalar_t__ Hour; scalar_t__ Day; } ;
typedef  TYPE_1__ EFI_TIME ;

/* Variables and functions */
 int** CumulativeDays ; 
 int SECSPERDAY ; 
 int SECSPERHOUR ; 
 int isleap (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
to_efi_time(EFI_TIME *efi_time, time_t time)
{
	int lyear, month;
	time_t seconds;

	if (time >= 0) {
		efi_time->Year = 1970;
		lyear = isleap(efi_time->Year);
		month = 13;
		seconds = CumulativeDays[lyear][month] * SECSPERDAY;
                while (time > seconds) {
			time -= seconds;
			efi_time->Year++;
			lyear = isleap(efi_time->Year);
			seconds = CumulativeDays[lyear][month] * SECSPERDAY;
		}

		efi_time->Month = 0;
                while (time >
		    CumulativeDays[lyear][month] * SECSPERDAY) {
			efi_time->Month++;
		}

		month = efi_time->Month - 1;
		time -= CumulativeDays[lyear][month] * SECSPERDAY;

		for (efi_time->Day = 0; time > SECSPERDAY; efi_time->Day++)
			time -= SECSPERDAY;

		for (efi_time->Hour = 0; time > SECSPERHOUR; efi_time->Hour++)
			time -= SECSPERHOUR;

		for (efi_time->Minute = 0; time > 60; efi_time->Minute++)
			time -= 60;

		efi_time->Second = time;
		efi_time->Nanosecond = 0;
		efi_time->TimeZone = 0;
		efi_time->Daylight = 0;
	} else {
		memset(efi_time, 0, sizeof(EFI_TIME));
	}
}