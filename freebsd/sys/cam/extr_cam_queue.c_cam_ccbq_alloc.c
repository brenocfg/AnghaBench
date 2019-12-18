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
struct cam_ccbq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMCCBQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ cam_ccbq_init (struct cam_ccbq*,int) ; 
 int /*<<< orphan*/  free (struct cam_ccbq*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

struct cam_ccbq *
cam_ccbq_alloc(int openings)
{
	struct cam_ccbq *ccbq;

	ccbq = (struct cam_ccbq *)malloc(sizeof(*ccbq), M_CAMCCBQ, M_NOWAIT);
	if (ccbq == NULL) {
		printf("cam_ccbq_alloc: - cannot malloc!\n");
		return (NULL);
	}
	if (cam_ccbq_init(ccbq, openings) != 0) {
		free(ccbq, M_CAMCCBQ);
		return (NULL);		
	}
	
	return (ccbq);
}