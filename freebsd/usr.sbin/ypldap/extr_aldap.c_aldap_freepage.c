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
struct aldap_page_control {struct aldap_page_control* cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct aldap_page_control*) ; 

void
aldap_freepage(struct aldap_page_control *page)
{
	free(page->cookie);
	free(page);
}