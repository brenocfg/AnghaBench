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
struct conf {int conf_isns_period; int conf_isns_timeout; int conf_timeout; int conf_maxproc; scalar_t__ conf_debug; int /*<<< orphan*/  conf_isns; int /*<<< orphan*/  conf_pports; int /*<<< orphan*/  conf_portal_groups; int /*<<< orphan*/  conf_ports; int /*<<< orphan*/  conf_auth_groups; int /*<<< orphan*/  conf_targets; int /*<<< orphan*/  conf_luns; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct conf* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

struct conf *
conf_new(void)
{
	struct conf *conf;

	conf = calloc(1, sizeof(*conf));
	if (conf == NULL)
		log_err(1, "calloc");
	TAILQ_INIT(&conf->conf_luns);
	TAILQ_INIT(&conf->conf_targets);
	TAILQ_INIT(&conf->conf_auth_groups);
	TAILQ_INIT(&conf->conf_ports);
	TAILQ_INIT(&conf->conf_portal_groups);
	TAILQ_INIT(&conf->conf_pports);
	TAILQ_INIT(&conf->conf_isns);

	conf->conf_isns_period = 900;
	conf->conf_isns_timeout = 5;
	conf->conf_debug = 0;
	conf->conf_timeout = 60;
	conf->conf_maxproc = 30;

	return (conf);
}