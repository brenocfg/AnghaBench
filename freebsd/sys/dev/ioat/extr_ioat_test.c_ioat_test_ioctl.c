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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  IOAT_DMATEST 128 
 int /*<<< orphan*/  ioat_dma_test (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ioat_test_ioctl(struct cdev *dev, unsigned long cmd, caddr_t arg, int flag,
    struct thread *td)
{

	switch (cmd) {
	case IOAT_DMATEST:
		ioat_dma_test(arg);
		break;
	default:
		return (EINVAL);
	}
	return (0);
}