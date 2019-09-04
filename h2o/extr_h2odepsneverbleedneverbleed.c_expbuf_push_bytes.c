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
struct expbuf_t {size_t end; } ;

/* Variables and functions */
 int /*<<< orphan*/  expbuf_push_num (struct expbuf_t*,size_t) ; 
 int /*<<< orphan*/  expbuf_reserve (struct expbuf_t*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 

__attribute__((used)) static void expbuf_push_bytes(struct expbuf_t *buf, const void *p, size_t l)
{
    expbuf_push_num(buf, l);
    expbuf_reserve(buf, l);
    memcpy(buf->end, p, l);
    buf->end += l;
}