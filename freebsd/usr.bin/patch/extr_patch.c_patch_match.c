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
typedef  scalar_t__ LINENUM ;

/* Variables and functions */
 scalar_t__ canonicalize ; 
 char* ifetch (scalar_t__,int) ; 
 scalar_t__ input_lines ; 
 scalar_t__ last_line_missing_eol ; 
 unsigned short pch_line_len (scalar_t__) ; 
 scalar_t__ pch_ptrn_lines () ; 
 char* pfetch (scalar_t__) ; 
 int /*<<< orphan*/  similar (char const*,char const*,unsigned short) ; 
 scalar_t__ strnNE (char const*,char const*,unsigned short) ; 

__attribute__((used)) static bool
patch_match(LINENUM base, LINENUM offset, LINENUM fuzz)
{
	LINENUM		pline = 1 + fuzz;
	LINENUM		iline;
	LINENUM		pat_lines = pch_ptrn_lines() - fuzz;
	const char	*ilineptr;
	const char	*plineptr;
	unsigned short	plinelen;

	/* Patch does not match if we don't have any more context to use */
	if (pline > pat_lines)
		return false;
	for (iline = base + offset + fuzz; pline <= pat_lines; pline++, iline++) {
		ilineptr = ifetch(iline, offset >= 0);
		if (ilineptr == NULL)
			return false;
		plineptr = pfetch(pline);
		plinelen = pch_line_len(pline);
		if (canonicalize) {
			if (!similar(ilineptr, plineptr, plinelen))
				return false;
		} else if (strnNE(ilineptr, plineptr, plinelen))
			return false;
		if (iline == input_lines) {
			/*
			 * We are looking at the last line of the file.
			 * If the file has no eol, the patch line should
			 * not have one either and vice-versa. Note that
			 * plinelen > 0.
			 */
			if (last_line_missing_eol) {
				if (plineptr[plinelen - 1] == '\n')
					return false;
			} else {
				if (plineptr[plinelen - 1] != '\n')
					return false;
			}
		}
	}
	return true;
}