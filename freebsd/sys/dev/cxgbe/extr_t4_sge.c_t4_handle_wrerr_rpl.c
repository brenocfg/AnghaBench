#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_9__ {int eqid; int* val; int /*<<< orphan*/  mv_pkd; int /*<<< orphan*/  pfn_vfn; int /*<<< orphan*/  cidx; } ;
struct TYPE_8__ {int eqid; int* wrhdr; int /*<<< orphan*/  pfn_vfn; int /*<<< orphan*/  cidx; } ;
struct TYPE_7__ {int regaddr; int regval; } ;
struct TYPE_6__ {int* info; } ;
struct TYPE_10__ {TYPE_4__ acl; TYPE_3__ wr; TYPE_2__ hwmodule; TYPE_1__ exception; } ;
struct fw_error_cmd {int op_to_type; TYPE_5__ u; } ;
struct adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FW_ERROR_CMD ; 
#define  FW_ERROR_TYPE_ACL 131 
#define  FW_ERROR_TYPE_EXCEPTION 130 
#define  FW_ERROR_TYPE_HWMODULE 129 
#define  FW_ERROR_TYPE_WR 128 
 scalar_t__ G_FW_ERROR_CMD_FATAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_ERROR_CMD_MV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_ERROR_CMD_PFN (int /*<<< orphan*/ ) ; 
 int G_FW_ERROR_CMD_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_FW_ERROR_CMD_VFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32toh (int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int nitems (int*) ; 

__attribute__((used)) static int
t4_handle_wrerr_rpl(struct adapter *adap, const __be64 *rpl)
{
	u8 opcode = *(const u8 *)rpl;
	const struct fw_error_cmd *e = (const void *)rpl;
	unsigned int i;

	if (opcode != FW_ERROR_CMD) {
		log(LOG_ERR,
		    "%s: Received WRERR_RPL message with opcode %#x\n",
		    device_get_nameunit(adap->dev), opcode);
		return (EINVAL);
	}
	log(LOG_ERR, "%s: FW_ERROR (%s) ", device_get_nameunit(adap->dev),
	    G_FW_ERROR_CMD_FATAL(be32toh(e->op_to_type)) ? "fatal" :
	    "non-fatal");
	switch (G_FW_ERROR_CMD_TYPE(be32toh(e->op_to_type))) {
	case FW_ERROR_TYPE_EXCEPTION:
		log(LOG_ERR, "exception info:\n");
		for (i = 0; i < nitems(e->u.exception.info); i++)
			log(LOG_ERR, "%s%08x", i == 0 ? "\t" : " ",
			    be32toh(e->u.exception.info[i]));
		log(LOG_ERR, "\n");
		break;
	case FW_ERROR_TYPE_HWMODULE:
		log(LOG_ERR, "HW module regaddr %08x regval %08x\n",
		    be32toh(e->u.hwmodule.regaddr),
		    be32toh(e->u.hwmodule.regval));
		break;
	case FW_ERROR_TYPE_WR:
		log(LOG_ERR, "WR cidx %d PF %d VF %d eqid %d hdr:\n",
		    be16toh(e->u.wr.cidx),
		    G_FW_ERROR_CMD_PFN(be16toh(e->u.wr.pfn_vfn)),
		    G_FW_ERROR_CMD_VFN(be16toh(e->u.wr.pfn_vfn)),
		    be32toh(e->u.wr.eqid));
		for (i = 0; i < nitems(e->u.wr.wrhdr); i++)
			log(LOG_ERR, "%s%02x", i == 0 ? "\t" : " ",
			    e->u.wr.wrhdr[i]);
		log(LOG_ERR, "\n");
		break;
	case FW_ERROR_TYPE_ACL:
		log(LOG_ERR, "ACL cidx %d PF %d VF %d eqid %d %s",
		    be16toh(e->u.acl.cidx),
		    G_FW_ERROR_CMD_PFN(be16toh(e->u.acl.pfn_vfn)),
		    G_FW_ERROR_CMD_VFN(be16toh(e->u.acl.pfn_vfn)),
		    be32toh(e->u.acl.eqid),
		    G_FW_ERROR_CMD_MV(be16toh(e->u.acl.mv_pkd)) ? "vlanid" :
		    "MAC");
		for (i = 0; i < nitems(e->u.acl.val); i++)
			log(LOG_ERR, " %02x", e->u.acl.val[i]);
		log(LOG_ERR, "\n");
		break;
	default:
		log(LOG_ERR, "type %#x\n",
		    G_FW_ERROR_CMD_TYPE(be32toh(e->op_to_type)));
		return (EINVAL);
	}
	return (0);
}