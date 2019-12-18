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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  pkt_dname_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_ttl_rdata (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
skip_pkt_rr(sldns_buffer* pkt)
{
	if(sldns_buffer_remaining(pkt) < 1) return 0;
	if(!pkt_dname_len(pkt))
		return 0;
	if(sldns_buffer_remaining(pkt) < 4) return 0;
	sldns_buffer_skip(pkt, 4); /* type and class */
	if(!skip_ttl_rdata(pkt))
		return 0;
	return 1;
}