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
struct TYPE_2__ {int /*<<< orphan*/  mesh; } ;
struct worker {TYPE_1__ env; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_delete_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_flush_requestlist(RES* ssl, struct worker* worker)
{
	mesh_delete_all(worker->env.mesh);
	send_ok(ssl);
}