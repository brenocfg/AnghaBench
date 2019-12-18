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
struct statbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct fd {TYPE_1__ devpts; } ;

/* Variables and functions */
 int /*<<< orphan*/  devpts_stat_num (int /*<<< orphan*/ ,struct statbuf*) ; 

__attribute__((used)) static int devpts_fstat(struct fd *fd, struct statbuf *stat) {
    devpts_stat_num(fd->devpts.num, stat);
    return 0;
}