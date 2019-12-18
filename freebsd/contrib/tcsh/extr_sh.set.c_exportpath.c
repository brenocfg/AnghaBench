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
 int /*<<< orphan*/  PATHSEP ; 
 int /*<<< orphan*/  STRKPATH ; 
 int /*<<< orphan*/  STRRparen ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Strbuf_finish (struct Strbuf*) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 scalar_t__ eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsetenv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
exportpath(Char **val)
{
    struct Strbuf buf = Strbuf_INIT;
    Char    	*exppath;

    if (val)
	while (*val) {
	    Strbuf_append(&buf, *val++);
	    if (*val == 0 || eq(*val, STRRparen))
		break;
	    Strbuf_append1(&buf, PATHSEP);
	}
    exppath = Strbuf_finish(&buf);
    cleanup_push(exppath, xfree);
    tsetenv(STRKPATH, exppath);
    cleanup_until(exppath);
}