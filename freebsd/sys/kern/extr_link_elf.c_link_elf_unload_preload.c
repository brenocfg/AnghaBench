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
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pathname; } ;

/* Variables and functions */
 int /*<<< orphan*/  preload_delete_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
link_elf_unload_preload(linker_file_t file)
{

	if (file->pathname != NULL)
		preload_delete_name(file->pathname);
}