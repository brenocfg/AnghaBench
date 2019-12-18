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
struct open_file {int /*<<< orphan*/  f_devdata; TYPE_1__* f_dev; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_2__ {int (* dv_strategy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*,size_t*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F_READ ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*,size_t*) ; 

__attribute__((used)) static int
ioget(struct open_file *fd, daddr_t lsec, void *buf, size_t size)
{
    size_t rsize;
    int rv;

    /* Make sure we get full read or error. */
    rsize = 0;
    rv = (fd->f_dev->dv_strategy)(fd->f_devdata, F_READ, lsec,
        size, buf, &rsize);
    if ((rv == 0) && (size != rsize))
        rv = EIO;
    return (rv);
}