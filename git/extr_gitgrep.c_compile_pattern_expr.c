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
struct grep_pat {int dummy; } ;
struct grep_expr {int dummy; } ;

/* Variables and functions */
 struct grep_expr* compile_pattern_or (struct grep_pat**) ; 

__attribute__((used)) static struct grep_expr *compile_pattern_expr(struct grep_pat **list)
{
	return compile_pattern_or(list);
}