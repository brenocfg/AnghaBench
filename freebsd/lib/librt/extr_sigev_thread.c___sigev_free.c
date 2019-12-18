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
struct sigev_node {int /*<<< orphan*/  sn_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct sigev_node*) ; 

void
__sigev_free(struct sigev_node *sn)
{
	_pthread_attr_destroy(&sn->sn_attr);
	free(sn);
}