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
struct fns_wrapper_baton {int /*<<< orphan*/  old_baton; TYPE_1__* vtable; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* token_discard_all ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
token_discard_all(void *baton)
{
  struct fns_wrapper_baton *fwb = baton;
  fwb->vtable->token_discard_all(fwb->old_baton);
}