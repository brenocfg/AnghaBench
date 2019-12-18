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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 size_t LDNS_MAX_DOMAINLEN ; 
 size_t sldns_buffer_read_u8 (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t
query_dname_len(sldns_buffer* query)
{
	size_t len = 0;
	size_t labellen;
	while(1) {
		if(sldns_buffer_remaining(query) < 1)
			return 0; /* parse error, need label len */
		labellen = sldns_buffer_read_u8(query);
		if(labellen&0xc0)
			return 0; /* no compression allowed in queries */
		len += labellen + 1;
		if(len > LDNS_MAX_DOMAINLEN)
			return 0; /* too long */
		if(labellen == 0)
			return len;
		if(sldns_buffer_remaining(query) < labellen)
			return 0; /* parse error, need content */
		sldns_buffer_skip(query, (ssize_t)labellen);
	}
}