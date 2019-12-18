#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockopt_data {int valsize; scalar_t__ kbuf; } ;
struct nat44_cfg_redir {int dummy; } ;
struct nat44_cfg_nat {int redir_cnt; int /*<<< orphan*/  name; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {TYPE_1__ head; } ;
struct TYPE_6__ {TYPE_2__ ntlv; } ;
typedef  TYPE_3__ ipfw_obj_header ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  nat44_config (struct ip_fw_chain*,struct nat44_cfg_nat*) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 

__attribute__((used)) static int
nat44_cfg(struct ip_fw_chain *chain, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	ipfw_obj_header *oh;
	struct nat44_cfg_nat *ucfg;
	int id;
	size_t read;
	char *errptr;

	/* Check minimum header size */
	if (sd->valsize < (sizeof(*oh) + sizeof(*ucfg)))
		return (EINVAL);

	oh = (ipfw_obj_header *)sd->kbuf;

	/* Basic length checks for TLVs */
	if (oh->ntlv.head.length != sizeof(oh->ntlv))
		return (EINVAL);

	ucfg = (struct nat44_cfg_nat *)(oh + 1);

	/* Check if name is properly terminated and looks like number */
	if (strnlen(ucfg->name, sizeof(ucfg->name)) == sizeof(ucfg->name))
		return (EINVAL);
	id = strtol(ucfg->name, &errptr, 10);
	if (id == 0 || *errptr != '\0')
		return (EINVAL);

	read = sizeof(*oh) + sizeof(*ucfg);
	/* Check number of redirs */
	if (sd->valsize < read + ucfg->redir_cnt*sizeof(struct nat44_cfg_redir))
		return (EINVAL);

	nat44_config(chain, ucfg);
	return (0);
}