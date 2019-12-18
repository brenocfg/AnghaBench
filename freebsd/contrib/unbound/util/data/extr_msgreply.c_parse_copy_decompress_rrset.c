#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  hash; void* key; void* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/ * dname; int /*<<< orphan*/  dname_len; int /*<<< orphan*/  flags; } ;
struct ub_packed_rrset_key {TYPE_2__ entry; TYPE_1__ rk; } ;
struct rrset_parse {int /*<<< orphan*/  hash; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/  type; int /*<<< orphan*/  dname; int /*<<< orphan*/  dname_len; int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {int /*<<< orphan*/  trust; } ;
struct msg_parse {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  dname_pkt_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rrset_trust (struct msg_parse*,struct rrset_parse*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_create_rrset (int /*<<< orphan*/ *,struct rrset_parse*,struct packed_rrset_data**,struct regional*) ; 
 scalar_t__ regional_alloc (struct regional*,int /*<<< orphan*/ ) ; 

int
parse_copy_decompress_rrset(sldns_buffer* pkt, struct msg_parse* msg,
	struct rrset_parse *pset, struct regional* region, 
	struct ub_packed_rrset_key* pk)
{
	struct packed_rrset_data* data;
	pk->rk.flags = pset->flags;
	pk->rk.dname_len = pset->dname_len;
	if(region)
		pk->rk.dname = (uint8_t*)regional_alloc(
			region, pset->dname_len);
	else	pk->rk.dname = 
			(uint8_t*)malloc(pset->dname_len);
	if(!pk->rk.dname)
		return 0;
	/** copy & decompress dname */
	dname_pkt_copy(pkt, pk->rk.dname, pset->dname);
	/** copy over type and class */
	pk->rk.type = htons(pset->type);
	pk->rk.rrset_class = pset->rrset_class;
	/** read data part. */
	if(!parse_create_rrset(pkt, pset, &data, region))
		return 0;
	pk->entry.data = (void*)data;
	pk->entry.key = (void*)pk;
	pk->entry.hash = pset->hash;
	data->trust = get_rrset_trust(msg, pset);
	return 1;
}