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
struct TYPE_2__ {int /*<<< orphan*/  root; scalar_t__ count; } ;
struct mesh_area {int /*<<< orphan*/  qbuf_bak; int /*<<< orphan*/  histogram; TYPE_1__ all; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mesh_area*) ; 
 int /*<<< orphan*/  mesh_delete_helper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timehist_delete (int /*<<< orphan*/ ) ; 

void 
mesh_delete(struct mesh_area* mesh)
{
	if(!mesh)
		return;
	/* free all query states */
	while(mesh->all.count)
		mesh_delete_helper(mesh->all.root);
	timehist_delete(mesh->histogram);
	sldns_buffer_free(mesh->qbuf_bak);
	free(mesh);
}