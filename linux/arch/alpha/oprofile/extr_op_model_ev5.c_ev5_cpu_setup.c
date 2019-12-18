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
struct op_register_config {int /*<<< orphan*/  reset_values; int /*<<< orphan*/  freq; int /*<<< orphan*/  proc_mode; int /*<<< orphan*/  mux_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  wrperfmon (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ev5_cpu_setup (void *x)
{
	struct op_register_config *reg = x;

	wrperfmon(2, reg->mux_select);
	wrperfmon(3, reg->proc_mode);
	wrperfmon(4, reg->freq);
	wrperfmon(6, reg->reset_values);
}