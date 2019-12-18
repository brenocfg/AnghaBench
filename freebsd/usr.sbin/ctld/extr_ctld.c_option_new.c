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
struct options {int dummy; } ;
struct option {void* o_value; void* o_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct options*,struct option*,int /*<<< orphan*/ ) ; 
 struct option* calloc (int,int) ; 
 void* checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 int /*<<< orphan*/  o_next ; 
 struct option* option_find (struct options*,char const*) ; 

struct option *
option_new(struct options *options, const char *name, const char *value)
{
	struct option *o;

	o = option_find(options, name);
	if (o != NULL) {
		log_warnx("duplicated option \"%s\"", name);
		return (NULL);
	}

	o = calloc(1, sizeof(*o));
	if (o == NULL)
		log_err(1, "calloc");
	o->o_name = checked_strdup(name);
	o->o_value = checked_strdup(value);
	TAILQ_INSERT_TAIL(options, o, o_next);

	return (o);
}