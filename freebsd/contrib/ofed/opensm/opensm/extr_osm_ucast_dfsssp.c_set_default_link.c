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
struct TYPE_3__ {int /*<<< orphan*/ * next; scalar_t__ weight; scalar_t__ to_port; scalar_t__ to; scalar_t__ from_port; scalar_t__ from; scalar_t__ guid; } ;
typedef  TYPE_1__ link_t ;

/* Variables and functions */

__attribute__((used)) static inline void set_default_link(link_t * link)
{
	link->guid = 0;
	link->from = 0;
	link->from_port = 0;
	link->to = 0;
	link->to_port = 0;
	link->weight = 0;
	link->next = NULL;
}