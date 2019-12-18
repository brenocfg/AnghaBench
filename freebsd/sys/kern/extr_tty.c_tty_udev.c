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
struct tty {scalar_t__ t_dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  NODEV ; 
 int /*<<< orphan*/  dev2udev (scalar_t__) ; 

dev_t
tty_udev(struct tty *tp)
{

	if (tp->t_dev)
		return (dev2udev(tp->t_dev));
	else
		return (NODEV);
}