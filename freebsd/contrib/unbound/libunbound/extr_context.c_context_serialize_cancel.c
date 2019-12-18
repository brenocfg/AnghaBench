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
typedef  int uint32_t ;
struct ctx_query {scalar_t__ querynum; } ;

/* Variables and functions */
 int UB_LIBCMD_CANCEL ; 
 scalar_t__ reallocarray (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,int) ; 

uint8_t* 
context_serialize_cancel(struct ctx_query* q, uint32_t* len)
{
	/* format of cancel:
	 * 	o uint32 cmd
	 * 	o uint32 async-id */
	uint8_t* p = (uint8_t*)reallocarray(NULL, sizeof(uint32_t), 2);
	if(!p) return NULL;
	*len = 2*sizeof(uint32_t);
	sldns_write_uint32(p, UB_LIBCMD_CANCEL);
	sldns_write_uint32(p+sizeof(uint32_t), (uint32_t)q->querynum);
	return p;
}