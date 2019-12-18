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
struct defined_value {void* d_value; void* d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct defined_value*,int /*<<< orphan*/ ) ; 
 struct defined_value* calloc (int,int) ; 
 void* checked_strdup (char const*) ; 
 int /*<<< orphan*/  d_next ; 
 char* defined_find (char const*) ; 
 int /*<<< orphan*/  defined_values ; 
 int /*<<< orphan*/  log_debugx (char*,char const*,char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_errx (int,char*,char const*) ; 

__attribute__((used)) static void
defined_add(const char *name, const char *value)
{
	struct defined_value *d;
	const char *found;

	found = defined_find(name);
	if (found != NULL)
		log_errx(1, "variable %s already defined", name);

	log_debugx("defining variable %s=%s", name, value);

	d = calloc(1, sizeof(*d));
	if (d == NULL)
		log_err(1, "calloc");
	d->d_name = checked_strdup(name);
	d->d_value = checked_strdup(value);

	TAILQ_INSERT_TAIL(&defined_values, d, d_next);
}