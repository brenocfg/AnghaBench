#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int crc_ver_init; int config_refresh; int config_ncdl; } ;
typedef  TYPE_1__ nvram_header_t ;
typedef  int /*<<< orphan*/  nvram_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  _nvram_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvram_get (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* nvram_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvram_set (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int _nvram_rehash(nvram_handle_t *h)
{
	nvram_header_t *header = nvram_header(h);
	char buf[] = "0xXXXXXXXX", *name, *value, *eq;

	/* (Re)initialize hash table */
	_nvram_free(h);

	/* Parse and set "name=value\0 ... \0\0" */
	name = (char *) &header[1];

	for (; *name; name = value + strlen(value) + 1) {
		if (!(eq = strchr(name, '=')))
			break;
		*eq = '\0';
		value = eq + 1;
		nvram_set(h, name, value);
		*eq = '=';
	}

	/* Set special SDRAM parameters */
	if (!nvram_get(h, "sdram_init")) {
		sprintf(buf, "0x%04X", (uint16_t)(header->crc_ver_init >> 16));
		nvram_set(h, "sdram_init", buf);
	}
	if (!nvram_get(h, "sdram_config")) {
		sprintf(buf, "0x%04X", (uint16_t)(header->config_refresh & 0xffff));
		nvram_set(h, "sdram_config", buf);
	}
	if (!nvram_get(h, "sdram_refresh")) {
		sprintf(buf, "0x%04X",
			(uint16_t)((header->config_refresh >> 16) & 0xffff));
		nvram_set(h, "sdram_refresh", buf);
	}
	if (!nvram_get(h, "sdram_ncdl")) {
		sprintf(buf, "0x%08X", header->config_ncdl);
		nvram_set(h, "sdram_ncdl", buf);
	}

	return 0;
}