#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {char* str; } ;
struct TYPE_4__ {TYPE_1__ value; int /*<<< orphan*/ * action; int /*<<< orphan*/ * directive; } ;

/* Variables and functions */
 TYPE_2__* dialogrc_config ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gauge_color ; 
 int /*<<< orphan*/  setattr ; 

void
dialogrc_free(void)
{
	char *value;
	uint32_t n;

	for (n = 0; dialogrc_config[n].directive != NULL; n++) {
		if (dialogrc_config[n].action != &setattr)
			continue;
		value = dialogrc_config[n].value.str;
		if (value != NULL && value != gauge_color) {
			free(dialogrc_config[n].value.str);
			dialogrc_config[n].value.str = NULL;
		}
	}
}