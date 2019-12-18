#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct TYPE_6__ {scalar_t__ _compress; } ;
typedef  TYPE_2__ sldns_rr_descriptor ;

/* Variables and functions */
 scalar_t__ LDNS_RR_COMPRESS ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 TYPE_2__ const* sldns_rr_descript (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const sldns_rr_descriptor*
type_rdata_compressable(struct ub_packed_rrset_key* key)
{
	uint16_t t = ntohs(key->rk.type);
	if(sldns_rr_descript(t) && 
		sldns_rr_descript(t)->_compress == LDNS_RR_COMPRESS)
		return sldns_rr_descript(t);
	return 0;
}