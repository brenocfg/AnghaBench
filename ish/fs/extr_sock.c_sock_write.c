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
struct fd {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int realfs_write (struct fd*,void const*,size_t) ; 
 int /*<<< orphan*/  sock_translate_err (struct fd*,int*) ; 

__attribute__((used)) static ssize_t sock_write(struct fd *fd, const void *buf, size_t size) {
    int err = realfs_write(fd, buf, size);
    sock_translate_err(fd, &err);
    return err;
}