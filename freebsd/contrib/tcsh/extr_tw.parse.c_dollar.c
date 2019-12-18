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
struct Strbuf {int /*<<< orphan*/  s; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  QUOTE ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 char* Strbuf_finish (struct Strbuf*) ; 
 scalar_t__ expdollar (struct Strbuf*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

Char *
dollar(const Char *old)
{
    struct Strbuf buf = Strbuf_INIT;

    while (*old) {
	if (*old != '$')
	    Strbuf_append1(&buf, *old++);
	else {
	    if (expdollar(&buf, &old, QUOTE) == 0) {
		xfree(buf.s);
		return NULL;
	    }
	}
    }
    return Strbuf_finish(&buf);
}