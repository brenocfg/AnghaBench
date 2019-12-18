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
 int /*<<< orphan*/  html_reset_internal (void*) ; 
 int /*<<< orphan*/  id_unique ; 
 int /*<<< orphan*/  mandoc_ohash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
html_reset(void *p)
{
	html_reset_internal(p);
	mandoc_ohash_init(&id_unique, 4, 0);
}