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
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static int is_foreign_ident(const char *str)
{
	int i;

	if (!skip_prefix(str, "$Id: ", &str))
		return 0;
	for (i = 0; str[i]; i++) {
		if (isspace(str[i]) && str[i+1] != '$')
			return 1;
	}
	return 0;
}