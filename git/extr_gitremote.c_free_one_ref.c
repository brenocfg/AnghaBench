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
struct ref {struct ref* symref; struct ref* remote_status; struct ref* peer_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ref*) ; 

void free_one_ref(struct ref *ref)
{
	if (!ref)
		return;
	free_one_ref(ref->peer_ref);
	free(ref->remote_status);
	free(ref->symref);
	free(ref);
}