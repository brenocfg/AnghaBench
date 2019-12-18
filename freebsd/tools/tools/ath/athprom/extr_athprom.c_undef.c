#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ee_version; } ;

/* Variables and functions */
 TYPE_1__ eeprom ; 
 int /*<<< orphan*/  warnx (char*,char const*,int,int) ; 

__attribute__((used)) static void
undef(const char *what)
{
	warnx("%s undefined for version %d.%d format EEPROM", what,
	    eeprom.ee_version >> 12, eeprom.ee_version & 0xfff);
}