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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ net_read (int,void*,size_t) ; 

__attribute__((used)) static void
enet_read(int fd, void *buf, size_t len)
{
    ssize_t ret;

    ret = net_read (fd, buf, len);
    if (ret == 0)
	errx (1, "EOF in read");
    else if (ret < 0)
	errx (1, "read");
}