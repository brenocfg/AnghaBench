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

/* Variables and functions */
 int sldns_b32_pton_base (char const*,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int) ; 

int
sldns_b32_pton(const char* src, size_t src_sz, uint8_t* dst, size_t dst_sz)
{
	return sldns_b32_pton_base(src, src_sz, dst, dst_sz, 0, 1);
}