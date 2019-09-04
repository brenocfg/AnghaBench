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
struct diff_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit_line_0 (struct diff_options*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void emit_line(struct diff_options *o, const char *set, const char *reset,
		      const char *line, int len)
{
	emit_line_0(o, set, NULL, 0, reset, 0, line, len);
}