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
struct TYPE_3__ {int /*<<< orphan*/  dropped; int /*<<< orphan*/ * sw; scalar_t__ heap_id; int /*<<< orphan*/  state; scalar_t__ distance; int /*<<< orphan*/ * used_link; scalar_t__ hops; int /*<<< orphan*/ * links; scalar_t__ num_hca; scalar_t__ lid; scalar_t__ guid; } ;
typedef  TYPE_1__ vertex_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UNDISCOVERED ; 

__attribute__((used)) static inline void set_default_vertex(vertex_t * vertex)
{
	vertex->guid = 0;
	vertex->lid = 0;
	vertex->num_hca = 0;
	vertex->links = NULL;
	vertex->hops = 0;
	vertex->used_link = NULL;
	vertex->distance = 0;
	vertex->state = UNDISCOVERED;
	vertex->heap_id = 0;
	vertex->sw = NULL;
	vertex->dropped = FALSE;
}