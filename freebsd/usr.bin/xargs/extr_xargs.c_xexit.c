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

/* Variables and functions */
 int /*<<< orphan*/  exit (int const) ; 
 int /*<<< orphan*/  waitchildren (char const*,int) ; 

__attribute__((used)) static void
xexit(const char *name, const int exit_code) {
	waitchildren(name, 1);
	exit(exit_code);
}