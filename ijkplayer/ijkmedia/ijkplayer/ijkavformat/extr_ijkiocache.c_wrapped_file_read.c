#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int read_file_inner_error; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ IjkURLContext ;
typedef  TYPE_2__ IjkIOCacheContext ;

/* Variables and functions */
 scalar_t__ read (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int wrapped_file_read(IjkURLContext *h, void *dst, int size)
{
    IjkIOCacheContext *c   = h->priv_data;
    int ret;

    ret = (int)read(c->fd, dst, size);
    c->read_file_inner_error = ret < 0 ? ret : 0;
    return ret;
}