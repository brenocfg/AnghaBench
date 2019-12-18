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
struct camq {int array_size; int /*<<< orphan*/ ** queue_array; } ;
typedef  int /*<<< orphan*/  cam_pinfo ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bzero (struct camq*,int) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
camq_init(struct camq *camq, int size)
{
	bzero(camq, sizeof(*camq));
	camq->array_size = size;
	if (camq->array_size != 0) {
		camq->queue_array = (cam_pinfo**)malloc(size*sizeof(cam_pinfo*),
							M_CAMQ, M_NOWAIT);
		if (camq->queue_array == NULL) {
			printf("camq_init: - cannot malloc array!\n");
			return (1);
		}
		/*
		 * Heap algorithms like everything numbered from 1, so
		 * offset our pointer into the heap array by one element.
		 */
		camq->queue_array--;
	}
	return (0);
}