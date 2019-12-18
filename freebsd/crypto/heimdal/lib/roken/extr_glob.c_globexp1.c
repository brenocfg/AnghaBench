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
 scalar_t__ const CHAR_EOS ; 
 scalar_t__ const CHAR_LBRACE ; 
 scalar_t__ const CHAR_RBRACE ; 
 scalar_t__ g_strchr (scalar_t__ const*,scalar_t__ const) ; 
 int glob0 (scalar_t__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  globexp2 (scalar_t__ const*,scalar_t__ const*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int globexp1(const Char *pattern, glob_t *pglob)
{
	const Char* ptr = pattern;
	int rv;

	/* Protect a single {}, for find(1), like csh */
	if (pattern[0] == CHAR_LBRACE && pattern[1] == CHAR_RBRACE && pattern[2] == CHAR_EOS)
		return glob0(pattern, pglob);

	while ((ptr = (const Char *) g_strchr(ptr, CHAR_LBRACE)) != NULL)
		if (!globexp2(ptr, pattern, pglob, &rv))
			return rv;

	return glob0(pattern, pglob);
}