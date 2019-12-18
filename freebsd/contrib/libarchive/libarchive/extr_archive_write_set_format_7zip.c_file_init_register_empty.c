#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;
struct _7zip {TYPE_1__ empty_list; } ;

/* Variables and functions */

__attribute__((used)) static void
file_init_register_empty(struct _7zip *zip)
{
	zip->empty_list.first = NULL;
	zip->empty_list.last = &(zip->empty_list.first);
}