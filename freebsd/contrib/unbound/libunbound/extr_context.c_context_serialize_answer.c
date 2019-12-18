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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct ctx_query {TYPE_1__* res; scalar_t__ msg_security; scalar_t__ querynum; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_2__ {int /*<<< orphan*/  why_bogus; scalar_t__ was_ratelimited; } ;

/* Variables and functions */
 size_t UB_LIBCMD_ANSWER ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

uint8_t* 
context_serialize_answer(struct ctx_query* q, int err, sldns_buffer* pkt,
	uint32_t* len)
{
	/* answer format
	 * 	o uint32 cmd
	 * 	o uint32 id
	 * 	o uint32 error_code
	 * 	o uint32 msg_security
	 * 	o uint32 was_ratelimited
	 * 	o uint32 length of why_bogus string (+1 for eos); 0 absent.
	 * 	o why_bogus_string
	 * 	o the remainder is the answer msg from resolver lookup.
	 * 	  remainder can be length 0.
	 */
	size_t size_of_uint32s = 6 * sizeof(uint32_t);
	size_t pkt_len = pkt?sldns_buffer_remaining(pkt):0;
	size_t wlen = (pkt&&q->res->why_bogus)?strlen(q->res->why_bogus)+1:0;
	uint8_t* p;
	*len = size_of_uint32s + pkt_len + wlen;
	p = (uint8_t*)malloc(*len);
	if(!p) return NULL;
	sldns_write_uint32(p, UB_LIBCMD_ANSWER);
	sldns_write_uint32(p+sizeof(uint32_t), (uint32_t)q->querynum);
	sldns_write_uint32(p+2*sizeof(uint32_t), (uint32_t)err);
	sldns_write_uint32(p+3*sizeof(uint32_t), (uint32_t)q->msg_security);
	sldns_write_uint32(p+4*sizeof(uint32_t), (uint32_t)q->res->was_ratelimited);
	sldns_write_uint32(p+5*sizeof(uint32_t), (uint32_t)wlen);
	if(wlen > 0)
		memmove(p+size_of_uint32s, q->res->why_bogus, wlen);
	if(pkt_len > 0)
		memmove(p+size_of_uint32s+wlen,
			sldns_buffer_begin(pkt), pkt_len);
	return p;
}