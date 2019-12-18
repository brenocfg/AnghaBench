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
struct undefined_handler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct undefined_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  free (struct undefined_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uh_link ; 

void
remove_coproc_handler(void *cookie)
{
	struct undefined_handler *uh = cookie;

	LIST_REMOVE(uh, uh_link);
	free(uh, M_TEMP);
}