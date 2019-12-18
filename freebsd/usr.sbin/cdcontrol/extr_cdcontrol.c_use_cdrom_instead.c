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
 char* getenv (char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static char *
use_cdrom_instead(const char *old_envvar)
{
	char *device;

	device = getenv(old_envvar);
	if (device)
		warnx("%s environment variable deprecated, "
		    "please use CDROM in the future.", old_envvar);
	return device;
}