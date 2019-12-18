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
typedef  int /*<<< orphan*/  SCR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_SPACEW (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_GOTOW (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int /*<<< orphan*/  MEMCPY (char*,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  msgq_wstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
ex_unknown(SCR *sp, CHAR_T *cmd, size_t len)
{
	size_t blen;
	CHAR_T *bp;

	GET_SPACE_GOTOW(sp, bp, blen, len + 1);
	bp[len] = '\0';
	MEMCPY(bp, cmd, len);
	msgq_wstr(sp, M_ERR, bp, "098|The %s command is unknown");
	FREE_SPACEW(sp, bp, blen);

alloc_err:
	return;
}