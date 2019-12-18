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
struct option {scalar_t__ value; int /*<<< orphan*/  long_name; } ;
struct TYPE_2__ {int hexsz; } ;

/* Variables and functions */
 int DEFAULT_ABBREV ; 
 int MINIMUM_ABBREV ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strtol (char const*,char**,int) ; 
 TYPE_1__* the_hash_algo ; 

int parse_opt_abbrev_cb(const struct option *opt, const char *arg, int unset)
{
	int v;

	if (!arg) {
		v = unset ? 0 : DEFAULT_ABBREV;
	} else {
		if (!*arg)
			return error(_("option `%s' expects a numerical value"),
				     opt->long_name);
		v = strtol(arg, (char **)&arg, 10);
		if (*arg)
			return error(_("option `%s' expects a numerical value"),
				     opt->long_name);
		if (v && v < MINIMUM_ABBREV)
			v = MINIMUM_ABBREV;
		else if (v > the_hash_algo->hexsz)
			v = the_hash_algo->hexsz;
	}
	*(int *)(opt->value) = v;
	return 0;
}