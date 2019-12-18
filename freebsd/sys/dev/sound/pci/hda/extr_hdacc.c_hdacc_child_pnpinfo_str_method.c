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
struct hdacc_fg {int type; int subsystem_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct hdacc_fg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int) ; 

__attribute__((used)) static int
hdacc_child_pnpinfo_str_method(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	struct hdacc_fg *fg = device_get_ivars(child);

	snprintf(buf, buflen, "type=0x%02x subsystem=0x%08x",
	    fg->type, fg->subsystem_id);
	return (0);
}