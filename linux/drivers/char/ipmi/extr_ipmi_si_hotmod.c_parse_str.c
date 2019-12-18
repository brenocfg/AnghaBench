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
struct hotmod_vals {unsigned int val; scalar_t__ name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_warn (char*,char*,...) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int parse_str(const struct hotmod_vals *v, unsigned int *val, char *name,
		     const char **curr)
{
	char *s;
	int  i;

	s = strchr(*curr, ',');
	if (!s) {
		pr_warn("No hotmod %s given\n", name);
		return -EINVAL;
	}
	*s = '\0';
	s++;
	for (i = 0; v[i].name; i++) {
		if (strcmp(*curr, v[i].name) == 0) {
			*val = v[i].val;
			*curr = s;
			return 0;
		}
	}

	pr_warn("Invalid hotmod %s '%s'\n", name, *curr);
	return -EINVAL;
}