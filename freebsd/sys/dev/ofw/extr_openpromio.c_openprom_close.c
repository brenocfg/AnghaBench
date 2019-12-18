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

/* Variables and functions */
 scalar_t__ openprom_is_open ; 

__attribute__((used)) static int
openprom_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{

	openprom_is_open = 0;
	return (0);
}