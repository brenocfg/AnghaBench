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
struct dnup_node {TYPE_1__* sw; } ;
struct TYPE_2__ {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dnup_node*) ; 

__attribute__((used)) static void delete_dnup_node(struct dnup_node *u)
{
	u->sw->priv = NULL;
	free(u);
}