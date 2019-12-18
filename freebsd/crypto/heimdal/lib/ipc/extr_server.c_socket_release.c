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
struct client {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__* heim_sipc ;
struct TYPE_3__ {struct client* mech; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING_CLOSE ; 

__attribute__((used)) static int
socket_release(heim_sipc ctx)
{
    struct client *c = ctx->mech;
    c->flags |= WAITING_CLOSE;
    return 0;
}