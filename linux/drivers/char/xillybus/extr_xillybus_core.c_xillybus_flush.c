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
struct file {int f_mode; int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  HZ ; 
 int xillybus_myflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xillybus_flush(struct file *filp, fl_owner_t id)
{
	if (!(filp->f_mode & FMODE_WRITE))
		return 0;

	return xillybus_myflush(filp->private_data, HZ); /* 1 second timeout */
}