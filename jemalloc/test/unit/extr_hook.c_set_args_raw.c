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
 int /*<<< orphan*/  arg_args_raw ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,uintptr_t*,int) ; 

__attribute__((used)) static void
set_args_raw(uintptr_t *args_raw, int nargs) {
	memcpy(arg_args_raw, args_raw, sizeof(uintptr_t) * nargs);
}