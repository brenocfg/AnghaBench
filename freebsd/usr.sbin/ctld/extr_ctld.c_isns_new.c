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
struct isns {int /*<<< orphan*/  i_addr; int /*<<< orphan*/  i_ai; struct conf* i_conf; } ;
struct conf {int /*<<< orphan*/  conf_isns; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct isns*,int /*<<< orphan*/ ) ; 
 struct isns* calloc (int,int) ; 
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  i_next ; 
 int /*<<< orphan*/  isns_delete (struct isns*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ parse_addr_port (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int
isns_new(struct conf *conf, const char *addr)
{
	struct isns *isns;

	isns = calloc(1, sizeof(*isns));
	if (isns == NULL)
		log_err(1, "calloc");
	isns->i_conf = conf;
	TAILQ_INSERT_TAIL(&conf->conf_isns, isns, i_next);
	isns->i_addr = checked_strdup(addr);

	if (parse_addr_port(isns->i_addr, "3205", &isns->i_ai)) {
		log_warnx("invalid iSNS address %s", isns->i_addr);
		isns_delete(isns);
		return (1);
	}

	/*
	 * XXX: getaddrinfo(3) may return multiple addresses; we should turn
	 *	those into multiple servers.
	 */

	return (0);
}