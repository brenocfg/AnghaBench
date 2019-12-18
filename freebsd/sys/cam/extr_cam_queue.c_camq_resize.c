#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct camq {int entries; int array_size; int /*<<< orphan*/ ** queue_array; } ;
typedef  int /*<<< orphan*/  cam_pinfo ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_RESRC_UNAVAIL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_CAMQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int32_t
camq_resize(struct camq *queue, int new_size)
{
	cam_pinfo **new_array;

	KASSERT(new_size >= queue->entries, ("camq_resize: "
	    "New queue size can't accommodate queued entries (%d < %d).",
	    new_size, queue->entries));
	new_array = (cam_pinfo **)malloc(new_size * sizeof(cam_pinfo *),
					 M_CAMQ, M_NOWAIT);
	if (new_array == NULL) {
		/* Couldn't satisfy request */
		return (CAM_RESRC_UNAVAIL);
	}
	/*
	 * Heap algorithms like everything numbered from 1, so
	 * remember that our pointer into the heap array is offset
	 * by one element.
	 */
	if (queue->queue_array != NULL) {
		queue->queue_array++;
		bcopy(queue->queue_array, new_array,
		      queue->entries * sizeof(cam_pinfo *));
		free(queue->queue_array, M_CAMQ);
	}
	queue->queue_array = new_array-1;
	queue->array_size = new_size;
	return (CAM_REQ_CMP);
}