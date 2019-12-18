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
struct cam_devq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAMDEVQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ cam_devq_init (struct cam_devq*,int,int) ; 
 int /*<<< orphan*/  free (struct cam_devq*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

struct cam_devq *
cam_devq_alloc(int devices, int openings)
{
	struct cam_devq *devq;

	devq = (struct cam_devq *)malloc(sizeof(*devq), M_CAMDEVQ, M_NOWAIT);
	if (devq == NULL) {
		printf("cam_devq_alloc: - cannot malloc!\n");
		return (NULL);
	}
	if (cam_devq_init(devq, devices, openings) != 0) {
		free(devq, M_CAMDEVQ);
		return (NULL);
	}
	return (devq);
}