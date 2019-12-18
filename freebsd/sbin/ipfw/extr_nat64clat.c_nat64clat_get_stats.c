#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ipfw_nat64clat_stats {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  opheader; int /*<<< orphan*/  ntlv; } ;
typedef  TYPE_1__ ipfw_obj_header ;
typedef  int /*<<< orphan*/  ipfw_obj_ctlv ;

/* Variables and functions */
 int /*<<< orphan*/  IP_FW_NAT64CLAT_STATS ; 
 TYPE_1__* calloc (int,size_t) ; 
 scalar_t__ do_get3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (struct ipfw_nat64clat_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nat64clat_fill_ntlv (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nat64clat_get_stats(const char *name, uint8_t set,
    struct ipfw_nat64clat_stats *stats)
{
	ipfw_obj_header *oh;
	ipfw_obj_ctlv *oc;
	size_t sz;

	sz = sizeof(*oh) + sizeof(*oc) + sizeof(*stats);
	oh = calloc(1, sz);
	nat64clat_fill_ntlv(&oh->ntlv, name, set);
	if (do_get3(IP_FW_NAT64CLAT_STATS, &oh->opheader, &sz) == 0) {
		oc = (ipfw_obj_ctlv *)(oh + 1);
		memcpy(stats, oc + 1, sizeof(*stats));
		free(oh);
		return (0);
	}
	free(oh);
	return (-1);
}