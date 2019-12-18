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
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int EIO ; 

__attribute__((used)) static int
net_strategy(void *devdata, int rw, daddr_t blk, size_t size, char *buf,
    size_t *rsize)
{

	return (EIO);
}