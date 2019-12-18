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
typedef  int /*<<< orphan*/  filename ;
struct TYPE_2__ {int ee_version; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int PATH_MAX ; 
 TYPE_1__ eeprom ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static FILE *
opentemplate(const char *dir)
{
	char filename[PATH_MAX];
	FILE *fd;

	/* find the template using the eeprom version */
	snprintf(filename, sizeof(filename), "%s/eeprom-%d.%d",
	    dir, eeprom.ee_version >> 12, eeprom.ee_version & 0xfff);
	fd = fopen(filename, "r");
	if (fd == NULL && errno == ENOENT) {
		/* retry with just the major version */
		snprintf(filename, sizeof(filename), "%s/eeprom-%d",
		    dir, eeprom.ee_version >> 12);
		fd = fopen(filename, "r");
		if (fd != NULL)		/* XXX verbose */
			warnx("Using template file %s", filename);
	}
	return fd;
}