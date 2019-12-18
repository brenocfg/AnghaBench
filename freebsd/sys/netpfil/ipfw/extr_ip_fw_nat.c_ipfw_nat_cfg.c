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
struct sockopt {size_t sopt_valsize; } ;
struct nat44_cfg_redir {int /*<<< orphan*/  spool_cnt; int /*<<< orphan*/  proto; int /*<<< orphan*/  rport_cnt; int /*<<< orphan*/  pport_cnt; int /*<<< orphan*/  rport; int /*<<< orphan*/  pport; int /*<<< orphan*/  lport; int /*<<< orphan*/  raddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  laddr; int /*<<< orphan*/  mode; } ;
struct nat44_cfg_nat {int redir_cnt; int /*<<< orphan*/  mode; int /*<<< orphan*/  ip; int /*<<< orphan*/  if_name; int /*<<< orphan*/  name; } ;
struct cfg_redir_legacy {int /*<<< orphan*/  spool_cnt; int /*<<< orphan*/  proto; int /*<<< orphan*/  rport_cnt; int /*<<< orphan*/  pport_cnt; int /*<<< orphan*/  rport; int /*<<< orphan*/  pport; int /*<<< orphan*/  lport; int /*<<< orphan*/  raddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  laddr; int /*<<< orphan*/  mode; } ;
struct cfg_nat_legacy {scalar_t__ id; int redir_cnt; int /*<<< orphan*/  mode; int /*<<< orphan*/  ip; int /*<<< orphan*/  if_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_layer3_chain ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nat44_config (int /*<<< orphan*/ *,struct nat44_cfg_nat*) ; 
 size_t roundup2 (size_t,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 int sooptcopyin (struct sockopt*,char*,size_t,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipfw_nat_cfg(struct sockopt *sopt)
{
	struct cfg_nat_legacy *cfg;
	struct nat44_cfg_nat *ucfg;
	struct cfg_redir_legacy *rdir;
	struct nat44_cfg_redir *urdir;
	char *buf;
	size_t len, len2;
	int error, i;

	len = sopt->sopt_valsize;
	len2 = len + 128;

	/*
	 * Allocate 2x buffer to store converted structures.
	 * new redir_cfg has shrunk, so we're sure that
	 * new buffer size is enough.
	 */
	buf = malloc(roundup2(len, 8) + len2, M_TEMP, M_WAITOK | M_ZERO);
	error = sooptcopyin(sopt, buf, len, sizeof(struct cfg_nat_legacy));
	if (error != 0)
		goto out;

	cfg = (struct cfg_nat_legacy *)buf;
	if (cfg->id < 0) {
		error = EINVAL;
		goto out;
	}

	ucfg = (struct nat44_cfg_nat *)&buf[roundup2(len, 8)];
	snprintf(ucfg->name, sizeof(ucfg->name), "%d", cfg->id);
	strlcpy(ucfg->if_name, cfg->if_name, sizeof(ucfg->if_name));
	ucfg->ip = cfg->ip;
	ucfg->mode = cfg->mode;
	ucfg->redir_cnt = cfg->redir_cnt;

	if (len < sizeof(*cfg) + cfg->redir_cnt * sizeof(*rdir)) {
		error = EINVAL;
		goto out;
	}

	urdir = (struct nat44_cfg_redir *)(ucfg + 1);
	rdir = (struct cfg_redir_legacy *)(cfg + 1);
	for (i = 0; i < cfg->redir_cnt; i++) {
		urdir->mode = rdir->mode;
		urdir->laddr = rdir->laddr;
		urdir->paddr = rdir->paddr;
		urdir->raddr = rdir->raddr;
		urdir->lport = rdir->lport;
		urdir->pport = rdir->pport;
		urdir->rport = rdir->rport;
		urdir->pport_cnt = rdir->pport_cnt;
		urdir->rport_cnt = rdir->rport_cnt;
		urdir->proto = rdir->proto;
		urdir->spool_cnt = rdir->spool_cnt;

		urdir++;
		rdir++;
	}

	nat44_config(&V_layer3_chain, ucfg);

out:
	free(buf, M_TEMP);
	return (error);
}