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
#define  MM_ERROR 131 
#define  MM_HALT 130 
#define  MM_INFO 129 
#define  MM_WARNING 128 

__attribute__((used)) static const char *
sevinfo(int sev)
{

	switch (sev) {
	case MM_HALT:
		return ("HALT");
	case MM_ERROR:
		return ("ERROR");
	case MM_WARNING:
		return ("WARNING");
	case MM_INFO:
		return ("INFO");
	default:
		return (NULL);
	}
}