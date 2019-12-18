#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct fd {TYPE_1__ devpts; } ;
struct attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devpts_setattr_num (int /*<<< orphan*/ ,struct attr) ; 

__attribute__((used)) static int devpts_fsetattr(struct fd *fd, struct attr attr) {
    devpts_setattr_num(fd->devpts.num, attr);
    return 0;
}