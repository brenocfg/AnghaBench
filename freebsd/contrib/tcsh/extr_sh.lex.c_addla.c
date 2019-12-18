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
struct Strbuf {scalar_t__ len; scalar_t__ s; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Strbuf_appendn (struct Strbuf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 struct Strbuf labuf ; 
 scalar_t__ lap ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

void
addla(Char *cp)
{
    static struct Strbuf buf; /* = Strbuf_INIT; */

    buf.len = 0;
    Strbuf_appendn(&buf, labuf.s + lap, labuf.len - lap);
    labuf.len = 0;
    Strbuf_append(&labuf, cp);
    Strbuf_terminate(&labuf);
    Strbuf_appendn(&labuf, buf.s, buf.len);
    xfree(cp);
    lap = 0;
}