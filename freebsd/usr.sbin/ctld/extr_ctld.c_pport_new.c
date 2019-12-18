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
typedef  int /*<<< orphan*/  uint32_t ;
struct pport {int /*<<< orphan*/  pp_ports; int /*<<< orphan*/  pp_ctl_port; int /*<<< orphan*/  pp_name; struct conf* pp_conf; } ;
struct conf {int /*<<< orphan*/  conf_pports; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pport*,int /*<<< orphan*/ ) ; 
 struct pport* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  pp_next ; 

struct pport *
pport_new(struct conf *conf, const char *name, uint32_t ctl_port)
{
	struct pport *pp;

	pp = calloc(1, sizeof(*pp));
	if (pp == NULL)
		log_err(1, "calloc");
	pp->pp_conf = conf;
	pp->pp_name = checked_strdup(name);
	pp->pp_ctl_port = ctl_port;
	TAILQ_INIT(&pp->pp_ports);
	TAILQ_INSERT_TAIL(&conf->conf_pports, pp, pp_next);
	return (pp);
}