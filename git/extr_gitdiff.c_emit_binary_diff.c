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
typedef  int /*<<< orphan*/  mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_SYMBOL_BINARY_DIFF_HEADER ; 
 int /*<<< orphan*/  emit_binary_diff_body (struct diff_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_diff_symbol (struct diff_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_binary_diff(struct diff_options *o,
			     mmfile_t *one, mmfile_t *two)
{
	emit_diff_symbol(o, DIFF_SYMBOL_BINARY_DIFF_HEADER, NULL, 0, 0);
	emit_binary_diff_body(o, one, two);
	emit_binary_diff_body(o, two, one);
}