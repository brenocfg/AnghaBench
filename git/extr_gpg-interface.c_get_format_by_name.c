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
struct gpg_format {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct gpg_format*) ; 
 struct gpg_format* gpg_format ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct gpg_format *get_format_by_name(const char *str)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(gpg_format); i++)
		if (!strcmp(gpg_format[i].name, str))
			return gpg_format + i;
	return NULL;
}