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
typedef  int /*<<< orphan*/  u32 ;
struct fst_session {int dummy; } ;

/* Variables and functions */
 unsigned long FST_MAX_LLT_MS ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  fst_printf_session (struct fst_session*,int /*<<< orphan*/ ,char*,char const*,unsigned long) ; 
 int /*<<< orphan*/  fst_session_set_llt (struct fst_session*,int /*<<< orphan*/ ) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int fst_session_set_str_llt(struct fst_session *s, const char *llt_str)
{
	char *endp;
	long int llt = strtol(llt_str, &endp, 0);

	if (*endp || llt < 0 || (unsigned long int) llt > FST_MAX_LLT_MS) {
		fst_printf_session(s, MSG_WARNING,
				   "Cannot set llt %s: Invalid llt value (1..%u expected)",
				   llt_str, FST_MAX_LLT_MS);
		return -1;
	}
	fst_session_set_llt(s, (u32) llt);

	return 0;
}