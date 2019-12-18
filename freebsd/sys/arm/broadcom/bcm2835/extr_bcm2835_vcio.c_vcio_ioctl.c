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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  ptr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  IOCTL_MBOX_PROPERTY 128 
 int /*<<< orphan*/  M_VCIO ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int bcm2835_mbox_property (int*,int) ; 
 int copyin (void*,int*,int) ; 
 int copyout (int*,void*,int) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 
 int* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ ,int) ; 

int
vcio_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td)
{
    int error;
    void *ptr;
    uint32_t size;
    uint8_t *property;

    error = 0;
    switch(cmd) {
    case IOCTL_MBOX_PROPERTY:
    	memcpy (&ptr, arg, sizeof(ptr));
	error = copyin(ptr, &size, sizeof(size));

	if (error != 0)
		break;
	property = malloc(size, M_VCIO, M_WAITOK);

	error = copyin(ptr, property, size);
	if (error) {
		free(property, M_VCIO);
		break;
	}

	error = bcm2835_mbox_property(property, size);
	if (error) {
		free(property, M_VCIO);
		break;
	}

	error = copyout(property, ptr, size);
	free(property, M_VCIO);

	break;
    default:
	error = EINVAL;
	break;
    }
    return (error);
}