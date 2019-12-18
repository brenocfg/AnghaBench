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
typedef  enum MAD_FIELDS { ____Placeholder_MAD_FIELDS } MAD_FIELDS ;

/* Variables and functions */
 int IB_PC_FIRST_F ; 
 int IB_PC_LAST_F ; 
 int /*<<< orphan*/  add_suppressed (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mad_field_name (int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static void calculate_suppressed_fields(char *str)
{
	enum MAD_FIELDS f;
	char *val, *lasts = NULL;
	char *tmp = strdup(str);

	val = strtok_r(tmp, ",", &lasts);
	while (val) {
		for (f = IB_PC_FIRST_F; f <= IB_PC_LAST_F; f++)
			if (strcmp(val, mad_field_name(f)) == 0)
				add_suppressed(f);
		val = strtok_r(NULL, ",", &lasts);
	}

	free(tmp);
}