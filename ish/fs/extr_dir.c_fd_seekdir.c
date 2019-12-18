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
struct fd {unsigned long offset; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* seekdir ) (struct fd*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fd*,unsigned long) ; 

__attribute__((used)) static void fd_seekdir(struct fd *fd, unsigned long off) {
    fd->offset = off;
    if (fd->ops->seekdir)
        fd->ops->seekdir(fd, off);
}