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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct rrset_parse {scalar_t__ hash; size_t dname_len; scalar_t__ type; scalar_t__ rrset_class; scalar_t__ flags; int /*<<< orphan*/  dname; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  scalar_t__ hashvalue_type ;

/* Variables and functions */
 scalar_t__ dname_pkt_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rrset_parse_equals(struct rrset_parse* p, sldns_buffer* pkt, hashvalue_type h, 
	uint32_t rrset_flags, uint8_t* dname, size_t dnamelen, 
	uint16_t type, uint16_t dclass)
{
	if(p->hash == h && p->dname_len == dnamelen && p->type == type &&
		p->rrset_class == dclass && p->flags == rrset_flags &&
		dname_pkt_compare(pkt, dname, p->dname) == 0)
		return 1;
	return 0;
}