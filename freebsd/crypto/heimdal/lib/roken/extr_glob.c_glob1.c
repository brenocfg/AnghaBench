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
typedef  int /*<<< orphan*/  glob_t ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ CHAR_EOS ; 
 int /*<<< orphan*/  MaxPathLen ; 
 int glob2 (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
glob1(Char *pattern, glob_t *pglob, size_t *limit)
{
	Char pathbuf[MaxPathLen+1];

	/* A null pathname is invalid -- POSIX 1003.1 sect. 2.4. */
	if (*pattern == CHAR_EOS)
		return(0);
	return(glob2(pathbuf, pathbuf, pattern, pglob, limit));
}