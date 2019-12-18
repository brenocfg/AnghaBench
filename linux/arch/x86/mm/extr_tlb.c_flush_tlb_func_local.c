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
struct flush_tlb_info {int dummy; } ;
typedef  enum tlb_flush_reason { ____Placeholder_tlb_flush_reason } tlb_flush_reason ;

/* Variables and functions */
 int /*<<< orphan*/  flush_tlb_func_common (struct flush_tlb_info const*,int,int) ; 

__attribute__((used)) static void flush_tlb_func_local(const void *info, enum tlb_flush_reason reason)
{
	const struct flush_tlb_info *f = info;

	flush_tlb_func_common(f, true, reason);
}