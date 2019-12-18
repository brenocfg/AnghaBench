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
struct tid_info {scalar_t__ type; int atype; } ;
struct tables_config {int algo_count; struct table_algo** algo; struct table_algo** def_algo; } ;
struct table_algo {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IPFW_TABLE_MAXTYPE ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct table_algo *
find_table_algo(struct tables_config *tcfg, struct tid_info *ti, char *name)
{
	int i, l;
	struct table_algo *ta;

	if (ti->type > IPFW_TABLE_MAXTYPE)
		return (NULL);

	/* Search by index */
	if (ti->atype != 0) {
		if (ti->atype > tcfg->algo_count)
			return (NULL);
		return (tcfg->algo[ti->atype]);
	}

	if (name == NULL) {
		/* Return default algorithm for given type if set */
		return (tcfg->def_algo[ti->type]);
	}

	/* Search by name */
	/* TODO: better search */
	for (i = 1; i <= tcfg->algo_count; i++) {
		ta = tcfg->algo[i];

		/*
		 * One can supply additional algorithm
		 * parameters so we compare only the first word
		 * of supplied name:
		 * 'addr:chash hsize=32'
		 * '^^^^^^^^^'
		 *
		 */
		l = strlen(ta->name);
		if (strncmp(name, ta->name, l) != 0)
			continue;
		if (name[l] != '\0' && name[l] != ' ')
			continue;
		/* Check if we're requesting proper table type */
		if (ti->type != 0 && ti->type != ta->type)
			return (NULL);
		return (ta);
	}

	return (NULL);
}