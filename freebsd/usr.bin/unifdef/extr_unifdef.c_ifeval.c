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
typedef  scalar_t__ Linetype ;

/* Variables and functions */
 scalar_t__ LT_ERROR ; 
 scalar_t__ LT_IF ; 
 int constexpr ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  eval_ops ; 
 scalar_t__ eval_table (int /*<<< orphan*/ ,long*,char const**) ; 
 scalar_t__ killconsts ; 

__attribute__((used)) static Linetype
ifeval(const char **cpp)
{
	Linetype ret;
	long val = 0;

	debug("eval %s", *cpp);
	constexpr = killconsts ? false : true;
	ret = eval_table(eval_ops, &val, cpp);
	debug("eval = %d", val);
	return (constexpr ? LT_IF : ret == LT_ERROR ? LT_IF : ret);
}