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
struct trapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_HANDLE_HMI ; 
 int OPAL_SUCCESS ; 
 int opal_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
opal_hmi_handler(struct trapframe *frame)
{
	int err;

	err = opal_call(OPAL_HANDLE_HMI);

	if (err == OPAL_SUCCESS)
		return (0);

	printf("HMI handler failed!  OPAL error code: %d\n", err);

	return (-1);
}