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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  xwrite (int,char const*,int) ; 

__attribute__((used)) static void child_error_fn(const char *err, va_list params)
{
	const char msg[] = "error() should not be called in child\n";
	xwrite(2, msg, sizeof(msg) - 1);
}