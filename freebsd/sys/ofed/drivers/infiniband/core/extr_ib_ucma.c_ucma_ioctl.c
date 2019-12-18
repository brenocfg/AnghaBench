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
struct file {int dummy; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  FIOASYNC 129 
#define  FIONBIO 128 

__attribute__((used)) static long
ucma_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	switch (cmd) {
	case FIONBIO:
	case FIOASYNC:
		return (0);
	default:
		return (-ENOTTY);
	}
}