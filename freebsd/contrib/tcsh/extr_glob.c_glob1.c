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
struct strbuf {int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  glob_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ EOS ; 
 int glob2 (struct strbuf*,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 struct strbuf strbuf_INIT ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
glob1(Char *pattern, glob_t *pglob, int no_match)
{
    struct strbuf pathbuf = strbuf_INIT;
    int err;

    /*
     * a null pathname is invalid -- POSIX 1003.1 sect. 2.4.
     */
    if (*pattern == EOS)
	return (0);
    err = glob2(&pathbuf, pattern, pglob, no_match);
    xfree(pathbuf.s);
    return err;
}