#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int str_longlen; } ;
struct TYPE_6__ {TYPE_1__ tbl; struct TYPE_6__* child; struct TYPE_6__* next; } ;
typedef  TYPE_2__ FILEDESC ;

/* Variables and functions */
 int /*<<< orphan*/  get_tbl (TYPE_2__*) ; 

__attribute__((used)) static int
maxlen_in_list(FILEDESC *list)
{
	FILEDESC	*fp;
	int		len, maxlen;

	maxlen = 0;
	for (fp = list; fp != NULL; fp = fp->next) {
		if (fp->child != NULL) {
			if ((len = maxlen_in_list(fp->child)) > maxlen)
				maxlen = len;
		}
		else {
			get_tbl(fp);
			if (fp->tbl.str_longlen > (unsigned int)maxlen)
				maxlen = fp->tbl.str_longlen;
		}
	}

	return (maxlen);
}