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
typedef  int /*<<< orphan*/  sz ;
struct expbuf_t {size_t* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  expbuf_reserve (struct expbuf_t*,size_t) ; 
 scalar_t__ read_nbytes (int,size_t*,size_t) ; 

__attribute__((used)) static int expbuf_read(struct expbuf_t *buf, int fd)
{
    size_t sz;

    if (read_nbytes(fd, &sz, sizeof(sz)) != 0)
        return -1;
    expbuf_reserve(buf, sz);
    if (read_nbytes(fd, buf->end, sz) != 0)
        return -1;
    buf->end += sz;
    return 0;
}