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
struct target {int /*<<< orphan*/  t_ports; struct conf* t_conf; int /*<<< orphan*/ * t_name; } ;
struct conf {int /*<<< orphan*/  conf_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct target*,int /*<<< orphan*/ ) ; 
 struct target* calloc (int,int) ; 
 int /*<<< orphan*/ * checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  t_next ; 
 struct target* target_find (struct conf*,char const*) ; 
 int /*<<< orphan*/  tolower (int /*<<< orphan*/ ) ; 
 int valid_iscsi_name (char const*) ; 

struct target *
target_new(struct conf *conf, const char *name)
{
	struct target *targ;
	int i, len;

	targ = target_find(conf, name);
	if (targ != NULL) {
		log_warnx("duplicated target \"%s\"", name);
		return (NULL);
	}
	if (valid_iscsi_name(name) == false) {
		log_warnx("target name \"%s\" is invalid", name);
		return (NULL);
	}
	targ = calloc(1, sizeof(*targ));
	if (targ == NULL)
		log_err(1, "calloc");
	targ->t_name = checked_strdup(name);

	/*
	 * RFC 3722 requires us to normalize the name to lowercase.
	 */
	len = strlen(name);
	for (i = 0; i < len; i++)
		targ->t_name[i] = tolower(targ->t_name[i]);

	targ->t_conf = conf;
	TAILQ_INIT(&targ->t_ports);
	TAILQ_INSERT_TAIL(&conf->conf_targets, targ, t_next);

	return (targ);
}