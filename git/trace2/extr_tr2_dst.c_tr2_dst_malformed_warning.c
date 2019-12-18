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
struct tr2_dst {int /*<<< orphan*/  sysenv_var; } ;

/* Variables and functions */
 int /*<<< orphan*/  tr2_sysenv_display_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void tr2_dst_malformed_warning(struct tr2_dst *dst,
				      const char *tgt_value)
{
	warning("trace2: unknown value for '%s': '%s'",
		tr2_sysenv_display_name(dst->sysenv_var), tgt_value);
}