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
 int /*<<< orphan*/  expbuf_reserve (struct expbuf_t*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void expbuf_push_str(struct expbuf_t *buf, const char *s)
{
    size_t l = strlen(s) + 1;
    expbuf_reserve(buf, l);
    memcpy(buf->end, s, l);
    buf->end += l;
}