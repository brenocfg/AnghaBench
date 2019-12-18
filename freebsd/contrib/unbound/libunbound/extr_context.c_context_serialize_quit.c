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

/* Variables and functions */
 int /*<<< orphan*/  UB_LIBCMD_QUIT ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int*,int /*<<< orphan*/ ) ; 

uint8_t* 
context_serialize_quit(uint32_t* len)
{
	uint32_t* p = (uint32_t*)malloc(sizeof(uint32_t));
	if(!p)
		return NULL;
	*len = sizeof(uint32_t);
	sldns_write_uint32(p, UB_LIBCMD_QUIT);
	return (uint8_t*)p;
}