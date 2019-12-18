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
struct sockopt_data {size_t valsize; } ;
struct nat44_cfg_nat {scalar_t__ size; int /*<<< orphan*/  name; } ;
struct ip_fw_chain {int /*<<< orphan*/  nat; } ;
struct cfg_nat {TYPE_3__* lib; } ;
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {TYPE_1__ head; } ;
struct _ipfw_obj_header {TYPE_2__ ntlv; } ;
typedef  struct _ipfw_obj_header ipfw_obj_header ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;
struct TYPE_6__ {int /*<<< orphan*/ * logDesc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ESRCH ; 
 int /*<<< orphan*/  IPFW_UH_RLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_RUNLOCK (struct ip_fw_chain*) ; 
 scalar_t__ LIBALIAS_BUF_SIZE ; 
 int /*<<< orphan*/  export_nat_cfg (struct cfg_nat*,struct nat44_cfg_nat*) ; 
 scalar_t__ ipfw_get_sopt_header (struct sockopt_data*,size_t) ; 
 scalar_t__ ipfw_get_sopt_space (struct sockopt_data*,scalar_t__) ; 
 struct cfg_nat* lookup_nat_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nat44_get_log(struct ip_fw_chain *chain, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	ipfw_obj_header *oh;
	struct nat44_cfg_nat *ucfg;
	struct cfg_nat *ptr;
	void *pbuf;
	size_t sz;

	sz = sizeof(*oh) + sizeof(*ucfg);
	/* Check minimum header size */
	if (sd->valsize < sz)
		return (EINVAL);

	oh = (struct _ipfw_obj_header *)ipfw_get_sopt_header(sd, sz);

	/* Basic length checks for TLVs */
	if (oh->ntlv.head.length != sizeof(oh->ntlv))
		return (EINVAL);

	ucfg = (struct nat44_cfg_nat *)(oh + 1);

	/* Check if name is properly terminated */
	if (strnlen(ucfg->name, sizeof(ucfg->name)) == sizeof(ucfg->name))
		return (EINVAL);

	IPFW_UH_RLOCK(chain);
	ptr = lookup_nat_name(&chain->nat, ucfg->name);
	if (ptr == NULL) {
		IPFW_UH_RUNLOCK(chain);
		return (ESRCH);
	}

	if (ptr->lib->logDesc == NULL) {
		IPFW_UH_RUNLOCK(chain);
		return (ENOENT);
	}

	export_nat_cfg(ptr, ucfg);
	
	/* Estimate memory amount */
	ucfg->size = sizeof(struct nat44_cfg_nat) + LIBALIAS_BUF_SIZE;
	if (sd->valsize < sz + sizeof(*oh)) {

		/*
		 * Submitted buffer size is not enough.
		 * WE've already filled in @ucfg structure with
		 * relevant info including size, so we
		 * can return. Buffer will be flushed automatically.
		 */
		IPFW_UH_RUNLOCK(chain);
		return (ENOMEM);
	}

	pbuf = (void *)ipfw_get_sopt_space(sd, LIBALIAS_BUF_SIZE);
	memcpy(pbuf, ptr->lib->logDesc, LIBALIAS_BUF_SIZE);
	
	IPFW_UH_RUNLOCK(chain);

	return (0);
}