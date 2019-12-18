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
struct TYPE_4__ {int /*<<< orphan*/  umad_fd; int /*<<< orphan*/  smps_on_wire; } ;
typedef  TYPE_1__ smp_engine_t ;
typedef  int /*<<< orphan*/  ibnd_smp_t ;
typedef  int /*<<< orphan*/  cl_map_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBND_ERROR (char*) ; 
 int /*<<< orphan*/ * cl_qmap_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cl_qmap_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_qmap_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_smp (TYPE_1__*) ; 
 int /*<<< orphan*/  umad_close_port (int /*<<< orphan*/ ) ; 

void smp_engine_destroy(smp_engine_t * engine)
{
	cl_map_item_t *item;
	ibnd_smp_t *smp;

	/* remove queued smps */
	smp = get_smp(engine);
	if (smp)
		IBND_ERROR("outstanding SMP's\n");
	for ( /* */ ; smp; smp = get_smp(engine))
		free(smp);

	/* remove smps from the wire queue */
	item = cl_qmap_head(&engine->smps_on_wire);
	if (item != cl_qmap_end(&engine->smps_on_wire))
		IBND_ERROR("outstanding SMP's on wire\n");
	for ( /* */ ; item != cl_qmap_end(&engine->smps_on_wire);
	     item = cl_qmap_head(&engine->smps_on_wire)) {
		cl_qmap_remove_item(&engine->smps_on_wire, item);
		free(item);
	}

	umad_close_port(engine->umad_fd);
}