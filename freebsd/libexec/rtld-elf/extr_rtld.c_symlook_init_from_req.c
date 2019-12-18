#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lockstate; int /*<<< orphan*/ * sym_out; int /*<<< orphan*/ * defobj_out; int /*<<< orphan*/  flags; int /*<<< orphan*/  ventry; int /*<<< orphan*/  hash_gnu; int /*<<< orphan*/  hash; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ SymLook ;

/* Variables and functions */

__attribute__((used)) static void
symlook_init_from_req(SymLook *dst, const SymLook *src)
{

	dst->name = src->name;
	dst->hash = src->hash;
	dst->hash_gnu = src->hash_gnu;
	dst->ventry = src->ventry;
	dst->flags = src->flags;
	dst->defobj_out = NULL;
	dst->sym_out = NULL;
	dst->lockstate = src->lockstate;
}