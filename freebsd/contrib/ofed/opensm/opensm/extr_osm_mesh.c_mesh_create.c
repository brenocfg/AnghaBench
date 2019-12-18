#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  osm_log_t ;
struct TYPE_8__ {void* class_count; void* class_type; } ;
typedef  TYPE_2__ mesh_t ;
struct TYPE_9__ {int num_switches; TYPE_1__* p_osm; } ;
typedef  TYPE_3__ lash_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSM_LOG_ERROR ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  mesh_delete (TYPE_2__*) ; 

__attribute__((used)) static mesh_t *mesh_create(lash_t *p_lash)
{
	osm_log_t *p_log = &p_lash->p_osm->log;
	mesh_t *mesh;

	if(!(mesh = calloc(1, sizeof(mesh_t))))
		goto err;

	if (!(mesh->class_type = calloc(p_lash->num_switches, sizeof(int))))
		goto err;

	if (!(mesh->class_count = calloc(p_lash->num_switches, sizeof(int))))
		goto err;

	return mesh;

err:
	mesh_delete(mesh);
	OSM_LOG(p_log, OSM_LOG_ERROR,
		"Failed allocating mesh - out of memory\n");
	return NULL;
}