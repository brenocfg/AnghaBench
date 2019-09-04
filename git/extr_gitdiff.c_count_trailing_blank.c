#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ptr; long size; } ;
typedef  TYPE_1__ mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  ws_blank_line (char*,int,unsigned int) ; 

__attribute__((used)) static int count_trailing_blank(mmfile_t *mf, unsigned ws_rule)
{
	char *ptr = mf->ptr;
	long size = mf->size;
	int cnt = 0;

	if (!size)
		return cnt;
	ptr += size - 1; /* pointing at the very end */
	if (*ptr != '\n')
		; /* incomplete line */
	else
		ptr--; /* skip the last LF */
	while (mf->ptr < ptr) {
		char *prev_eol;
		for (prev_eol = ptr; mf->ptr <= prev_eol; prev_eol--)
			if (*prev_eol == '\n')
				break;
		if (!ws_blank_line(prev_eol + 1, ptr - prev_eol, ws_rule))
			break;
		cnt++;
		ptr = prev_eol - 1;
	}
	return cnt;
}