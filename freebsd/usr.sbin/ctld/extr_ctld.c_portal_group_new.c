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
struct portal_group {scalar_t__ pg_tag; struct conf* pg_conf; int /*<<< orphan*/  pg_ports; int /*<<< orphan*/  pg_portals; int /*<<< orphan*/  pg_options; int /*<<< orphan*/  pg_name; } ;
struct conf {int /*<<< orphan*/  conf_portal_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct portal_group*,int /*<<< orphan*/ ) ; 
 struct portal_group* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 int /*<<< orphan*/  pg_next ; 
 struct portal_group* portal_group_find (struct conf*,char const*) ; 

struct portal_group *
portal_group_new(struct conf *conf, const char *name)
{
	struct portal_group *pg;

	pg = portal_group_find(conf, name);
	if (pg != NULL) {
		log_warnx("duplicated portal-group \"%s\"", name);
		return (NULL);
	}

	pg = calloc(1, sizeof(*pg));
	if (pg == NULL)
		log_err(1, "calloc");
	pg->pg_name = checked_strdup(name);
	TAILQ_INIT(&pg->pg_options);
	TAILQ_INIT(&pg->pg_portals);
	TAILQ_INIT(&pg->pg_ports);
	pg->pg_conf = conf;
	pg->pg_tag = 0;		/* Assigned later in conf_apply(). */
	TAILQ_INSERT_TAIL(&conf->conf_portal_groups, pg, pg_next);

	return (pg);
}