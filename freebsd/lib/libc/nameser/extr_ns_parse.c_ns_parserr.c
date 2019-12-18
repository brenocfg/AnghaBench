#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ns_sect ;
struct TYPE_6__ {int type; int rr_class; int rdlength; int /*<<< orphan*/ * rdata; scalar_t__ ttl; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ns_rr ;
struct TYPE_7__ {int _sect; int _rrnum; int* _counts; int _msg_ptr; int _eom; int /*<<< orphan*/  _msg; } ;
typedef  TYPE_2__ ns_msg ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  NS_GET16 (int,int) ; 
 int /*<<< orphan*/  NS_GET32 (scalar_t__,int) ; 
 int NS_INT16SZ ; 
 int NS_INT32SZ ; 
 int /*<<< orphan*/  NS_MAXDNAME ; 
 int /*<<< orphan*/  RETERR (int /*<<< orphan*/ ) ; 
 int dn_expand (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ns_s_max ; 
 int ns_s_qd ; 
 int ns_skiprr (int,int,int,int) ; 
 int /*<<< orphan*/  setsection (TYPE_2__*,int) ; 

int
ns_parserr(ns_msg *handle, ns_sect section, int rrnum, ns_rr *rr) {
	int b;
	int tmp;

	/* Make section right. */
	tmp = section;
	if (tmp < 0 || section >= ns_s_max)
		RETERR(ENODEV);
	if (section != handle->_sect)
		setsection(handle, section);

	/* Make rrnum right. */
	if (rrnum == -1)
		rrnum = handle->_rrnum;
	if (rrnum < 0 || rrnum >= handle->_counts[(int)section])
		RETERR(ENODEV);
	if (rrnum < handle->_rrnum)
		setsection(handle, section);
	if (rrnum > handle->_rrnum) {
		b = ns_skiprr(handle->_msg_ptr, handle->_eom, section,
			      rrnum - handle->_rrnum);

		if (b < 0)
			return (-1);
		handle->_msg_ptr += b;
		handle->_rrnum = rrnum;
	}

	/* Do the parse. */
	b = dn_expand(handle->_msg, handle->_eom,
		      handle->_msg_ptr, rr->name, NS_MAXDNAME);
	if (b < 0)
		return (-1);
	handle->_msg_ptr += b;
	if (handle->_msg_ptr + NS_INT16SZ + NS_INT16SZ > handle->_eom)
		RETERR(EMSGSIZE);
	NS_GET16(rr->type, handle->_msg_ptr);
	NS_GET16(rr->rr_class, handle->_msg_ptr);
	if (section == ns_s_qd) {
		rr->ttl = 0;
		rr->rdlength = 0;
		rr->rdata = NULL;
	} else {
		if (handle->_msg_ptr + NS_INT32SZ + NS_INT16SZ > handle->_eom)
			RETERR(EMSGSIZE);
		NS_GET32(rr->ttl, handle->_msg_ptr);
		NS_GET16(rr->rdlength, handle->_msg_ptr);
		if (handle->_msg_ptr + rr->rdlength > handle->_eom)
			RETERR(EMSGSIZE);
		rr->rdata = handle->_msg_ptr;
		handle->_msg_ptr += rr->rdlength;
	}
	if (++handle->_rrnum > handle->_counts[(int)section])
		setsection(handle, (ns_sect)((int)section + 1));

	/* All done. */
	return (0);
}