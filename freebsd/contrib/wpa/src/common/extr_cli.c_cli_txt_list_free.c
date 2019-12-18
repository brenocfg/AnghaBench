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
struct cli_txt_entry {struct cli_txt_entry* txt; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct cli_txt_entry*) ; 

void cli_txt_list_free(struct cli_txt_entry *e)
{
	dl_list_del(&e->list);
	os_free(e->txt);
	os_free(e);
}