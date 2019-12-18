#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct key_value {TYPE_3__* hint; } ;
struct TYPE_4__ {int /*<<< orphan*/  cached; } ;
struct TYPE_5__ {TYPE_1__ Rh; } ;
struct TYPE_6__ {int /*<<< orphan*/  status; TYPE_2__ v; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS_INITIALIZED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void
randomcoll_init_hint(struct key_value *kv, void *hash)
{

	memcpy(kv->hint->v.Rh.cached, hash, sizeof(kv->hint->v.Rh.cached));
	kv->hint->status = HS_INITIALIZED;
}