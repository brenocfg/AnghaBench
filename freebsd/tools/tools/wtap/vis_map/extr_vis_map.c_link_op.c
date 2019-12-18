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
struct link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VISIOCTLLINK ; 
 int /*<<< orphan*/  dev ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
link_op(struct link *l)
{
	if (ioctl(dev, VISIOCTLLINK, l) < 0) {
		printf("error making a link operation\n");
	}
}