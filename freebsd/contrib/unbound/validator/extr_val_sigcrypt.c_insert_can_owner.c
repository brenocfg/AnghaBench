#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {size_t dname_len; scalar_t__* dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  dname_remove_label (scalar_t__**,size_t*) ; 
 int dname_signame_label_count (scalar_t__*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  query_dname_tolower (scalar_t__*) ; 
 scalar_t__* sldns_buffer_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,scalar_t__*,size_t) ; 

__attribute__((used)) static void
insert_can_owner(sldns_buffer* buf, struct ub_packed_rrset_key* k,
	uint8_t* sig, uint8_t** can_owner, size_t* can_owner_len)
{
	int rrsig_labels = (int)sig[3];
	int fqdn_labels = dname_signame_label_count(k->rk.dname);
	*can_owner = sldns_buffer_current(buf);
	if(rrsig_labels == fqdn_labels) {
		/* no change */
		sldns_buffer_write(buf, k->rk.dname, k->rk.dname_len);
		query_dname_tolower(*can_owner);
		*can_owner_len = k->rk.dname_len;
		return;
	}
	log_assert(rrsig_labels < fqdn_labels);
	/* *. | fqdn(rightmost rrsig_labels) */
	if(rrsig_labels < fqdn_labels) {
		int i;
		uint8_t* nm = k->rk.dname;
		size_t len = k->rk.dname_len;
		/* so skip fqdn_labels-rrsig_labels */
		for(i=0; i<fqdn_labels-rrsig_labels; i++) {
			dname_remove_label(&nm, &len);	
		}
		*can_owner_len = len+2;
		sldns_buffer_write(buf, (uint8_t*)"\001*", 2);
		sldns_buffer_write(buf, nm, len);
		query_dname_tolower(*can_owner);
	}
}