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
struct ip_fw_chain {int /*<<< orphan*/  nat; } ;
struct cfg_nat {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int length; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; TYPE_1__ head; } ;
typedef  TYPE_2__ ipfw_obj_ntlv ;
struct TYPE_6__ {TYPE_2__ ntlv; } ;
typedef  TYPE_3__ ipfw_obj_header ;
typedef  int /*<<< orphan*/  ip_fw3_opheader ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cfg_nat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _next ; 
 int /*<<< orphan*/  flush_nat_ptrs (struct ip_fw_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_nat_instance (struct cfg_nat*) ; 
 struct cfg_nat* lookup_nat_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strnlen (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nat44_destroy(struct ip_fw_chain *chain, ip_fw3_opheader *op3,
    struct sockopt_data *sd)
{
	ipfw_obj_header *oh;
	struct cfg_nat *ptr;
	ipfw_obj_ntlv *ntlv;

	/* Check minimum header size */
	if (sd->valsize < sizeof(*oh))
		return (EINVAL);

	oh = (ipfw_obj_header *)sd->kbuf;

	/* Basic length checks for TLVs */
	if (oh->ntlv.head.length != sizeof(oh->ntlv))
		return (EINVAL);

	ntlv = &oh->ntlv;
	/* Check if name is properly terminated */
	if (strnlen(ntlv->name, sizeof(ntlv->name)) == sizeof(ntlv->name))
		return (EINVAL);

	IPFW_UH_WLOCK(chain);
	ptr = lookup_nat_name(&chain->nat, ntlv->name);
	if (ptr == NULL) {
		IPFW_UH_WUNLOCK(chain);
		return (ESRCH);
	}
	IPFW_WLOCK(chain);
	LIST_REMOVE(ptr, _next);
	flush_nat_ptrs(chain, ptr->id);
	IPFW_WUNLOCK(chain);
	IPFW_UH_WUNLOCK(chain);

	free_nat_instance(ptr);

	return (0);
}