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
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ u_num; } ;
struct figpar_config {TYPE_1__ value; int /*<<< orphan*/ * action; scalar_t__ type; int /*<<< orphan*/ * directive; } ;

/* Variables and functions */
 struct figpar_config figpar_dummy_config ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

struct figpar_config *
get_config_option(struct figpar_config options[], const char *directive)
{
	uint32_t n;

	/* Check arguments */
	if (options == NULL || directive == NULL)
		return (&figpar_dummy_config);

	/* Loop through the array, return the index of the first match */
	for (n = 0; options[n].directive != NULL; n++)
		if (strcmp(options[n].directive, directive) == 0)
			return (&(options[n]));

	/* Re-initialize the dummy variable in case it was written to */
	figpar_dummy_config.directive	= NULL;
	figpar_dummy_config.type	= 0;
	figpar_dummy_config.action	= NULL;
	figpar_dummy_config.value.u_num	= 0;

	return (&figpar_dummy_config);
}