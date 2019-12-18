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
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct undefined_handler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uh_link ; 
 int /*<<< orphan*/ * undefined_handlers ; 

void
install_coproc_handler_static(int coproc, struct undefined_handler *uh)
{

	LIST_INSERT_HEAD(&undefined_handlers[coproc], uh, uh_link);
}