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
struct repository_format {int /*<<< orphan*/  partial_clone; int /*<<< orphan*/  work_tree; int /*<<< orphan*/  unknown_extensions; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_repository_format (struct repository_format*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void clear_repository_format(struct repository_format *format)
{
	string_list_clear(&format->unknown_extensions, 0);
	free(format->work_tree);
	free(format->partial_clone);
	init_repository_format(format);
}