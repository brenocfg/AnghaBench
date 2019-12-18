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
typedef  int uint64_t ;
struct trapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_HANDLE_HMI2 ; 
 int OPAL_HMI_FLAGS_TOD_TB_FAIL ; 
 int OPAL_SUCCESS ; 
 int opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vtophys (int*) ; 

__attribute__((used)) static int
opal_hmi_handler2(struct trapframe *frame)
{
	uint64_t flags;
	int err;

	flags = 0;
	err = opal_call(OPAL_HANDLE_HMI2, vtophys(&flags));

	if (flags & OPAL_HMI_FLAGS_TOD_TB_FAIL)
		panic("TOD/TB recovery failure");

	if (err == OPAL_SUCCESS)
		return (0);

	printf("HMI handler failed!  OPAL error code: %d\n", err);

	return (-1);
}