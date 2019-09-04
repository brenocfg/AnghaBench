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
struct expbuf_t {int start; } ;

/* Variables and functions */
 int expbuf_size (struct expbuf_t*) ; 
 int /*<<< orphan*/  memcpy (size_t*,int,int) ; 

__attribute__((used)) static int expbuf_shift_num(struct expbuf_t *buf, size_t *v)
{
    if (expbuf_size(buf) < sizeof(*v))
        return -1;
    memcpy(v, buf->start, sizeof(*v));
    buf->start += sizeof(*v);
    return 0;
}