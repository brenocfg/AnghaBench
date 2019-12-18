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
struct expbuf_t {char* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  expbuf_size (struct expbuf_t*) ; 
 char* memchr (char*,char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *expbuf_shift_str(struct expbuf_t *buf)
{
    char *nul = memchr(buf->start, '\0', expbuf_size(buf)), *ret;
    if (nul == NULL)
        return NULL;
    ret = buf->start;
    buf->start = nul + 1;
    return ret;
}