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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 scalar_t__ LABEL_IS_PTR (int) ; 
 int LDNS_MAX_LABELLEN ; 
 int /*<<< orphan*/  PTR_OFFSET (int,int) ; 
 int /*<<< orphan*/  hashlittle (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int* sldns_buffer_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tolower (unsigned char) ; 

hashvalue_type
dname_pkt_hash(sldns_buffer* pkt, uint8_t* dname, hashvalue_type h)
{
	uint8_t labuf[LDNS_MAX_LABELLEN+1];
	uint8_t lablen;
	int i;

	/* preserve case of query, make hash label by label */
	lablen = *dname++;
	while(lablen) {
		if(LABEL_IS_PTR(lablen)) {
			/* follow pointer */
			dname = sldns_buffer_at(pkt, PTR_OFFSET(lablen, *dname));
			lablen = *dname++;
			continue;
		}
		log_assert(lablen <= LDNS_MAX_LABELLEN);
		labuf[0] = lablen;
		i=0;
		while(lablen--) {
			labuf[++i] = (uint8_t)tolower((unsigned char)*dname);
			dname++;
		}
		h = hashlittle(labuf, labuf[0] + 1, h);
		lablen = *dname++;
	}

	return h;
}