#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  object; } ;
struct TYPE_4__ {TYPE_1__ shared; } ;
struct umtx_key {TYPE_2__ info; scalar_t__ shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

void
umtx_key_release(struct umtx_key *key)
{
	if (key->shared)
		vm_object_deallocate(key->info.shared.object);
}