#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dir; } ;
struct secpolicy {scalar_t__ policy; int state; int tcount; struct ipsecrequest** req; int /*<<< orphan*/  priority; int /*<<< orphan*/  id; TYPE_1__ spidx; } ;
struct sadb_x_policy {scalar_t__ sadb_x_policy_type; int /*<<< orphan*/  sadb_x_policy_len; int /*<<< orphan*/  sadb_x_policy_scope; int /*<<< orphan*/  sadb_x_policy_priority; int /*<<< orphan*/  sadb_x_policy_id; int /*<<< orphan*/  sadb_x_policy_dir; int /*<<< orphan*/  sadb_x_policy_exttype; } ;
struct sadb_x_ipsecrequest {size_t sadb_x_ipsecrequest_len; int /*<<< orphan*/  sadb_x_ipsecrequest_reqid; int /*<<< orphan*/  sadb_x_ipsecrequest_level; int /*<<< orphan*/  sadb_x_ipsecrequest_mode; int /*<<< orphan*/  sadb_x_ipsecrequest_proto; } ;
struct TYPE_6__ {scalar_t__ sa_len; } ;
struct TYPE_8__ {TYPE_2__ sa; } ;
struct TYPE_7__ {TYPE_4__ dst; TYPE_4__ src; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; int /*<<< orphan*/  proto; } ;
struct ipsecrequest {TYPE_3__ saidx; int /*<<< orphan*/  level; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  IPSEC_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPSEC_POLICYSCOPE_GLOBAL ; 
 int /*<<< orphan*/  IPSEC_POLICYSCOPE_IFNET ; 
 int /*<<< orphan*/  IPSEC_POLICYSCOPE_PCB ; 
 scalar_t__ IPSEC_POLICY_IPSEC ; 
#define  IPSEC_SPSTATE_IFNET 129 
#define  IPSEC_SPSTATE_PCB 128 
 size_t PFKEY_ALIGN8 (scalar_t__) ; 
 int /*<<< orphan*/  PFKEY_UNIT64 (size_t) ; 
 int /*<<< orphan*/  SADB_X_EXT_POLICY ; 
 int /*<<< orphan*/  bcopy (TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 

int
key_sp2msg(struct secpolicy *sp, void *request, size_t *len)
{
	struct sadb_x_ipsecrequest *xisr;
	struct sadb_x_policy *xpl;
	struct ipsecrequest *isr;
	size_t xlen, ilen;
	caddr_t p;
	int error, i;

	IPSEC_ASSERT(sp != NULL, ("null policy"));

	xlen = sizeof(*xpl);
	if (*len < xlen)
		return (EINVAL);

	error = 0;
	bzero(request, *len);
	xpl = (struct sadb_x_policy *)request;
	xpl->sadb_x_policy_exttype = SADB_X_EXT_POLICY;
	xpl->sadb_x_policy_type = sp->policy;
	xpl->sadb_x_policy_dir = sp->spidx.dir;
	xpl->sadb_x_policy_id = sp->id;
	xpl->sadb_x_policy_priority = sp->priority;
	switch (sp->state) {
	case IPSEC_SPSTATE_IFNET:
		xpl->sadb_x_policy_scope = IPSEC_POLICYSCOPE_IFNET;
		break;
	case IPSEC_SPSTATE_PCB:
		xpl->sadb_x_policy_scope = IPSEC_POLICYSCOPE_PCB;
		break;
	default:
		xpl->sadb_x_policy_scope = IPSEC_POLICYSCOPE_GLOBAL;
	}

	/* if is the policy for ipsec ? */
	if (sp->policy == IPSEC_POLICY_IPSEC) {
		p = (caddr_t)xpl + sizeof(*xpl);
		for (i = 0; i < sp->tcount; i++) {
			isr = sp->req[i];
			ilen = PFKEY_ALIGN8(sizeof(*xisr) +
			    isr->saidx.src.sa.sa_len +
			    isr->saidx.dst.sa.sa_len);
			xlen += ilen;
			if (xlen > *len) {
				error = ENOBUFS;
				/* Calculate needed size */
				continue;
			}
			xisr = (struct sadb_x_ipsecrequest *)p;
			xisr->sadb_x_ipsecrequest_len = ilen;
			xisr->sadb_x_ipsecrequest_proto = isr->saidx.proto;
			xisr->sadb_x_ipsecrequest_mode = isr->saidx.mode;
			xisr->sadb_x_ipsecrequest_level = isr->level;
			xisr->sadb_x_ipsecrequest_reqid = isr->saidx.reqid;

			p += sizeof(*xisr);
			bcopy(&isr->saidx.src, p, isr->saidx.src.sa.sa_len);
			p += isr->saidx.src.sa.sa_len;
			bcopy(&isr->saidx.dst, p, isr->saidx.dst.sa.sa_len);
			p += isr->saidx.dst.sa.sa_len;
		}
	}
	xpl->sadb_x_policy_len = PFKEY_UNIT64(xlen);
	if (error == 0)
		*len = xlen;
	else
		*len = sizeof(*xpl);
	return (error);
}