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
struct nat44_cfg_nat {int /*<<< orphan*/  name; int /*<<< orphan*/  if_name; int /*<<< orphan*/  mode; int /*<<< orphan*/  redir_cnt; int /*<<< orphan*/  ip; } ;
struct ip_fw_chain {int gencnt; int /*<<< orphan*/  nat; } ;
struct cfg_nat {int /*<<< orphan*/  redir_chain; int /*<<< orphan*/  ip; int /*<<< orphan*/  lib; int /*<<< orphan*/  mode; int /*<<< orphan*/  if_name; int /*<<< orphan*/  redir_cnt; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct cfg_nat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cfg_nat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibAliasInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LibAliasSetAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LibAliasSetMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _next ; 
 int /*<<< orphan*/  add_redir_spool_cfg (char*,struct cfg_nat*) ; 
 int /*<<< orphan*/  del_redir_spool_cfg (struct cfg_nat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_nat_ptrs (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_nat_instance (struct cfg_nat*) ; 
 struct cfg_nat* lookup_nat_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cfg_nat* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nat44_config(struct ip_fw_chain *chain, struct nat44_cfg_nat *ucfg)
{
	struct cfg_nat *ptr, *tcfg;
	int gencnt;

	/*
	 * Find/create nat rule.
	 */
	IPFW_UH_WLOCK(chain);
	gencnt = chain->gencnt;
	ptr = lookup_nat_name(&chain->nat, ucfg->name);
	if (ptr == NULL) {
		IPFW_UH_WUNLOCK(chain);
		/* New rule: allocate and init new instance. */
		ptr = malloc(sizeof(struct cfg_nat), M_IPFW, M_WAITOK | M_ZERO);
		ptr->lib = LibAliasInit(NULL);
		LIST_INIT(&ptr->redir_chain);
	} else {
		/* Entry already present: temporarily unhook it. */
		IPFW_WLOCK(chain);
		LIST_REMOVE(ptr, _next);
		flush_nat_ptrs(chain, ptr->id);
		IPFW_WUNLOCK(chain);
		IPFW_UH_WUNLOCK(chain);
	}

	/*
	 * Basic nat (re)configuration.
	 */
	ptr->id = strtol(ucfg->name, NULL, 10);
	/*
	 * XXX - what if this rule doesn't nat any ip and just
	 * redirect?
	 * do we set aliasaddress to 0.0.0.0?
	 */
	ptr->ip = ucfg->ip;
	ptr->redir_cnt = ucfg->redir_cnt;
	ptr->mode = ucfg->mode;
	strlcpy(ptr->if_name, ucfg->if_name, sizeof(ptr->if_name));
	LibAliasSetMode(ptr->lib, ptr->mode, ~0);
	LibAliasSetAddress(ptr->lib, ptr->ip);

	/*
	 * Redir and LSNAT configuration.
	 */
	/* Delete old cfgs. */
	del_redir_spool_cfg(ptr, &ptr->redir_chain);
	/* Add new entries. */
	add_redir_spool_cfg((char *)(ucfg + 1), ptr);
	IPFW_UH_WLOCK(chain);

	/* Extra check to avoid race with another ipfw_nat_cfg() */
	tcfg = NULL;
	if (gencnt != chain->gencnt)
	    tcfg = lookup_nat_name(&chain->nat, ucfg->name);
	IPFW_WLOCK(chain);
	if (tcfg != NULL)
		LIST_REMOVE(tcfg, _next);
	LIST_INSERT_HEAD(&chain->nat, ptr, _next);
	IPFW_WUNLOCK(chain);
	chain->gencnt++;

	IPFW_UH_WUNLOCK(chain);

	if (tcfg != NULL)
		free_nat_instance(ptr);
}