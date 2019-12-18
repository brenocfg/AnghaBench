#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* module_t ;
typedef  int /*<<< orphan*/  linker_file_t ;
struct TYPE_3__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */

linker_file_t
module_file(module_t mod)
{

	return (mod->file);
}