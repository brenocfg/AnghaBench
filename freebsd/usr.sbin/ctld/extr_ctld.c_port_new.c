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
struct target {int /*<<< orphan*/  t_ports; int /*<<< orphan*/  t_name; } ;
struct portal_group {int /*<<< orphan*/  pg_ports; int /*<<< orphan*/  pg_name; } ;
struct port {char* p_name; struct portal_group* p_portal_group; struct target* p_target; scalar_t__ p_ioctl_port; struct conf* p_conf; } ;
struct conf {int /*<<< orphan*/  conf_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct port*,int /*<<< orphan*/ ) ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct port* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,char*) ; 
 int /*<<< orphan*/  p_next ; 
 int /*<<< orphan*/  p_pgs ; 
 int /*<<< orphan*/  p_ts ; 
 int /*<<< orphan*/ * port_find (struct conf*,char*) ; 

struct port *
port_new(struct conf *conf, struct target *target, struct portal_group *pg)
{
	struct port *port;
	char *name;
	int ret;

	ret = asprintf(&name, "%s-%s", pg->pg_name, target->t_name);
	if (ret <= 0)
		log_err(1, "asprintf");
	if (port_find(conf, name) != NULL) {
		log_warnx("duplicate port \"%s\"", name);
		free(name);
		return (NULL);
	}
	port = calloc(1, sizeof(*port));
	if (port == NULL)
		log_err(1, "calloc");
	port->p_conf = conf;
	port->p_name = name;
	port->p_ioctl_port = 0;
	TAILQ_INSERT_TAIL(&conf->conf_ports, port, p_next);
	TAILQ_INSERT_TAIL(&target->t_ports, port, p_ts);
	port->p_target = target;
	TAILQ_INSERT_TAIL(&pg->pg_ports, port, p_pgs);
	port->p_portal_group = pg;
	return (port);
}