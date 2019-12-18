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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  enum ub_ctx_cmd { ____Placeholder_ub_ctx_cmd } ub_ctx_cmd ;

/* Variables and functions */
 int UB_LIBCMD_QUIT ; 
 int sldns_read_uint32 (int /*<<< orphan*/ *) ; 

enum ub_ctx_cmd context_serial_getcmd(uint8_t* p, uint32_t len)
{
	uint32_t v;
	if((size_t)len < sizeof(v))
		return UB_LIBCMD_QUIT;
	v = sldns_read_uint32(p);
	return v;
}