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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
#define  MFI_EVT_LOCALE_ALL 136 
#define  MFI_EVT_LOCALE_BBU 135 
#define  MFI_EVT_LOCALE_CLUSTER 134 
#define  MFI_EVT_LOCALE_CONFIG 133 
#define  MFI_EVT_LOCALE_CTRL 132 
#define  MFI_EVT_LOCALE_ENCL 131 
#define  MFI_EVT_LOCALE_LD 130 
#define  MFI_EVT_LOCALE_PD 129 
#define  MFI_EVT_LOCALE_SAS 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
format_locale(uint16_t locale)
{
	static char buffer[8];

	switch (locale) {
	case MFI_EVT_LOCALE_LD:
		return ("VOLUME");
	case MFI_EVT_LOCALE_PD:
		return ("DRIVE");
	case MFI_EVT_LOCALE_ENCL:
		return ("ENCL");
	case MFI_EVT_LOCALE_BBU:
		return ("BATTERY");
	case MFI_EVT_LOCALE_SAS:
		return ("SAS");
	case MFI_EVT_LOCALE_CTRL:
		return ("CTRL");
	case MFI_EVT_LOCALE_CONFIG:
		return ("CONFIG");
	case MFI_EVT_LOCALE_CLUSTER:
		return ("CLUSTER");
	case MFI_EVT_LOCALE_ALL:
		return ("ALL");
	default:
		snprintf(buffer, sizeof(buffer), "0x%04x", locale);
		return (buffer);
	}
}