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
struct conf {int /*<<< orphan*/  conf_auth_groups; } ;
struct auth_group {struct conf* ag_conf; int /*<<< orphan*/  ag_portals; int /*<<< orphan*/  ag_names; int /*<<< orphan*/  ag_auths; int /*<<< orphan*/  ag_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct auth_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag_next ; 
 struct auth_group* auth_group_find (struct conf*,char const*) ; 
 struct auth_group* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 

struct auth_group *
auth_group_new(struct conf *conf, const char *name)
{
	struct auth_group *ag;

	if (name != NULL) {
		ag = auth_group_find(conf, name);
		if (ag != NULL) {
			log_warnx("duplicated auth-group \"%s\"", name);
			return (NULL);
		}
	}

	ag = calloc(1, sizeof(*ag));
	if (ag == NULL)
		log_err(1, "calloc");
	if (name != NULL)
		ag->ag_name = checked_strdup(name);
	TAILQ_INIT(&ag->ag_auths);
	TAILQ_INIT(&ag->ag_names);
	TAILQ_INIT(&ag->ag_portals);
	ag->ag_conf = conf;
	TAILQ_INSERT_TAIL(&conf->conf_auth_groups, ag, ag_next);

	return (ag);
}