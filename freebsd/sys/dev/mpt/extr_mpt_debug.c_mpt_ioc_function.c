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
struct Error_Map {int Error_Code; char* Error_String; } ;

/* Variables and functions */
 struct Error_Map* IOC_Func ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static char *
mpt_ioc_function(int code)
{
	const struct Error_Map *status = IOC_Func;
	static char buf[64];
	while (status->Error_Code >= 0) {
		if (status->Error_Code == code)
			return status->Error_String;
		status++;
	}
	snprintf(buf, sizeof buf, "Unknown (0x%08x)", code);
	return buf;
}