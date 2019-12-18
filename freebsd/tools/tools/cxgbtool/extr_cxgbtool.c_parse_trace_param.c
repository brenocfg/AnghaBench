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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int parse_ipaddr (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int parse_val_mask_param (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strchr (char const*,char) ; 

__attribute__((used)) static int
parse_trace_param(const char *s, uint32_t *val, uint32_t *mask)
{
	return strchr(s, '.') ? parse_ipaddr(s, val, mask) :
				parse_val_mask_param(s, val, mask, 0xffffffffU);
}