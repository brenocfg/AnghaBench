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
typedef  int int8_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
#define  MFI_EVT_CLASS_CRITICAL 134 
#define  MFI_EVT_CLASS_DEAD 133 
#define  MFI_EVT_CLASS_DEBUG 132 
#define  MFI_EVT_CLASS_FATAL 131 
#define  MFI_EVT_CLASS_INFO 130 
#define  MFI_EVT_CLASS_PROGRESS 129 
#define  MFI_EVT_CLASS_WARNING 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
format_class(int8_t class)
{
	static char buffer[6];

	switch (class) {
	case MFI_EVT_CLASS_DEBUG:
		return ("debug");
	case MFI_EVT_CLASS_PROGRESS:
		return ("progress");
	case MFI_EVT_CLASS_INFO:
		return ("info");
	case MFI_EVT_CLASS_WARNING:
		return ("WARN");
	case MFI_EVT_CLASS_CRITICAL:
		return ("CRIT");
	case MFI_EVT_CLASS_FATAL:
		return ("FATAL");
	case MFI_EVT_CLASS_DEAD:
		return ("DEAD");
	default:
		snprintf(buffer, sizeof(buffer), "%d", class);
		return (buffer);
	}
}