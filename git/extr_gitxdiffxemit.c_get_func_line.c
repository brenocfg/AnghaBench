#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long nrec; } ;
struct TYPE_4__ {TYPE_2__ xdf1; } ;
typedef  TYPE_1__ xdfenv_t ;
typedef  int /*<<< orphan*/  xdemitconf_t ;
struct func_line {char* buf; long len; } ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 long match_func_rec (TYPE_2__*,int /*<<< orphan*/  const*,long,char*,long) ; 

__attribute__((used)) static long get_func_line(xdfenv_t *xe, xdemitconf_t const *xecfg,
			  struct func_line *func_line, long start, long limit)
{
	long l, size, step = (start > limit) ? -1 : 1;
	char *buf, dummy[1];

	buf = func_line ? func_line->buf : dummy;
	size = func_line ? sizeof(func_line->buf) : sizeof(dummy);

	for (l = start; l != limit && 0 <= l && l < xe->xdf1.nrec; l += step) {
		long len = match_func_rec(&xe->xdf1, xecfg, l, buf, size);
		if (len >= 0) {
			if (func_line)
				func_line->len = len;
			return l;
		}
	}
	return -1;
}