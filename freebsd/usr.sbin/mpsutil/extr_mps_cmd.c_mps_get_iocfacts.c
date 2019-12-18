#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_11__ {int /*<<< orphan*/  Function; } ;
typedef  TYPE_1__ MPI2_IOC_FACTS_REQUEST ;
typedef  TYPE_2__ MPI2_IOC_FACTS_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IOC_STATUS_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPI2_FUNCTION_IOC_FACTS ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 int mps_pass_command (int,TYPE_1__*,int,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mps_user_command (int,TYPE_1__*,int,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MPI2_IOC_FACTS_REPLY *
mps_get_iocfacts(int fd)
{
	MPI2_IOC_FACTS_REPLY *facts;
	MPI2_IOC_FACTS_REQUEST req;
	int error;

	facts = malloc(sizeof(MPI2_IOC_FACTS_REPLY));
	if (facts == NULL) {
		errno = ENOMEM;
		return (NULL);
	}

	bzero(&req, sizeof(MPI2_IOC_FACTS_REQUEST));
	req.Function = MPI2_FUNCTION_IOC_FACTS;

#if 1
	error = mps_pass_command(fd, &req, sizeof(MPI2_IOC_FACTS_REQUEST),
	    facts, sizeof(MPI2_IOC_FACTS_REPLY), NULL, 0, NULL, 0, 10);
#else
	error = mps_user_command(fd, &req, sizeof(MPI2_IOC_FACTS_REQUEST),
	    facts, sizeof(MPI2_IOC_FACTS_REPLY), NULL, 0, 0);
#endif
	if (error) {
		free(facts);
		return (NULL);
	}

	if (!IOC_STATUS_SUCCESS(facts->IOCStatus)) {
		free(facts);
		errno = EINVAL;
		return (NULL);
	}
	return (facts);
}