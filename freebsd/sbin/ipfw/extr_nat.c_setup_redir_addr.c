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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct nat44_cfg_spool {int /*<<< orphan*/  port; TYPE_1__ addr; } ;
struct nat44_cfg_redir {TYPE_1__ paddr; TYPE_1__ laddr; int /*<<< orphan*/  spool_cnt; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  REDIR_ADDR ; 
 int /*<<< orphan*/  StrToAddr (char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int
setup_redir_addr(char *buf, int *ac, char ***av)
{
	struct nat44_cfg_redir *r;
	char *sep;
	size_t space;

	r = (struct nat44_cfg_redir *)buf;
	r->mode = REDIR_ADDR;
	/* Skip nat44_cfg_redir at beginning of buf. */
	buf = &buf[sizeof(struct nat44_cfg_redir)];
	space = sizeof(struct nat44_cfg_redir);

	/* Extract local address. */
	if (strchr(**av, ',') != NULL) {
		struct nat44_cfg_spool *spool;

		/* Setup LSNAT server pool. */
		r->laddr.s_addr = INADDR_NONE;
		sep = strtok(**av, ",");
		while (sep != NULL) {
			spool = (struct nat44_cfg_spool *)buf;
			space += sizeof(struct nat44_cfg_spool);
			StrToAddr(sep, &spool->addr);
			spool->port = ~0;
			r->spool_cnt++;
			/* Point to the next possible nat44_cfg_spool. */
			buf = &buf[sizeof(struct nat44_cfg_spool)];
			sep = strtok(NULL, ",");
		}
	} else
		StrToAddr(**av, &r->laddr);
	(*av)++; (*ac)--;

	/* Extract public address. */
	StrToAddr(**av, &r->paddr);
	(*av)++; (*ac)--;

	return (space);
}