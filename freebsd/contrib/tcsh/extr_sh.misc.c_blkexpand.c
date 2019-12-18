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
struct Strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char) ; 
 int /*<<< orphan*/ * Strbuf_finish (struct Strbuf*) ; 

Char *
blkexpand(Char *const *av)
{
    struct Strbuf buf = Strbuf_INIT;

    for (; *av; av++) {
	Strbuf_append(&buf, *av);
	if (av[1])
	    Strbuf_append1(&buf, ' ');
    }
    return Strbuf_finish(&buf);
}