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
typedef  int uint32_t ;
struct ctx_query {TYPE_1__* res; scalar_t__ querynum; } ;
struct TYPE_2__ {int /*<<< orphan*/  qname; scalar_t__ qclass; scalar_t__ qtype; } ;

/* Variables and functions */
 int UB_LIBCMD_NEWQUERY ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

uint8_t* 
context_serialize_new_query(struct ctx_query* q, uint32_t* len)
{
	/* format for new query is
	 * 	o uint32 cmd
	 * 	o uint32 id
	 * 	o uint32 type
	 * 	o uint32 class
	 * 	o rest queryname (string)
	 */
	uint8_t* p;
	size_t slen = strlen(q->res->qname) + 1/*end of string*/;
	*len = sizeof(uint32_t)*4 + slen;
	p = (uint8_t*)malloc(*len);
	if(!p) return NULL;
	sldns_write_uint32(p, UB_LIBCMD_NEWQUERY);
	sldns_write_uint32(p+sizeof(uint32_t), (uint32_t)q->querynum);
	sldns_write_uint32(p+2*sizeof(uint32_t), (uint32_t)q->res->qtype);
	sldns_write_uint32(p+3*sizeof(uint32_t), (uint32_t)q->res->qclass);
	memmove(p+4*sizeof(uint32_t), q->res->qname, slen);
	return p;
}