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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LABEL_IS_PTR (scalar_t__) ; 
 size_t LDNS_MAX_DOMAINLEN ; 
 scalar_t__ LDNS_MAX_LABELLEN ; 
 int /*<<< orphan*/  PTR_OFFSET (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__* sldns_buffer_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dname_pkt_copy(sldns_buffer* pkt, uint8_t* to, uint8_t* dname)
{
	/* copy over the dname and decompress it at the same time */
	size_t len = 0;
	uint8_t lablen;
	lablen = *dname++;
	while(lablen) {
		if(LABEL_IS_PTR(lablen)) {
			/* follow pointer */
			dname = sldns_buffer_at(pkt, PTR_OFFSET(lablen, *dname));
			lablen = *dname++;
			continue;
		}
		log_assert(lablen <= LDNS_MAX_LABELLEN);
		len += (size_t)lablen+1;
		if(len >= LDNS_MAX_DOMAINLEN) {
			*to = 0; /* end the result prematurely */
			log_err("bad dname in dname_pkt_copy");
			return;
		}
		*to++ = lablen;
		memmove(to, dname, lablen);
		dname += lablen;
		to += lablen;
		lablen = *dname++;
	}
	/* copy last \0 */
	*to = 0;
}