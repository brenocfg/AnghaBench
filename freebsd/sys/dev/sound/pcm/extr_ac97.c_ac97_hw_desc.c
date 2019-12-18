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
typedef  int u_int32_t ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static const char*
ac97_hw_desc(u_int32_t id, const char* vname, const char* cname, char* buf)
{
	if (cname == NULL) {
		sprintf(buf, "Unknown AC97 Codec (id = 0x%08x)", id);
		return buf;
	}

	if (vname == NULL) vname = "Unknown";

	if (bootverbose) {
		sprintf(buf, "%s %s AC97 Codec (id = 0x%08x)", vname, cname, id);
	} else {
		sprintf(buf, "%s %s AC97 Codec", vname, cname);
	}
	return buf;
}