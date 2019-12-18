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
struct wpa_config {int dummy; } ;
struct global_parse_data {int (* get ) (char const*,struct wpa_config*,long,char*,size_t,int /*<<< orphan*/ ) ;scalar_t__ param1; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t NUM_GLOBAL_FIELDS ; 
 struct global_parse_data* global_fields ; 
 scalar_t__ os_strcmp (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (char const*,struct wpa_config*,long,char*,size_t,int /*<<< orphan*/ ) ; 

int wpa_config_get_value(const char *name, struct wpa_config *config,
			 char *buf, size_t buflen)
{
	size_t i;

	for (i = 0; i < NUM_GLOBAL_FIELDS; i++) {
		const struct global_parse_data *field = &global_fields[i];

		if (os_strcmp(name, field->name) != 0)
			continue;
		if (!field->get)
			break;
		return field->get(name, config, (long) field->param1,
				  buf, buflen, 0);
	}

	return -1;
}