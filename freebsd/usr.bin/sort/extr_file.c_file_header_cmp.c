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
struct file_header {scalar_t__ file_pos; int /*<<< orphan*/  si; int /*<<< orphan*/ * fr; } ;

/* Variables and functions */
 int list_coll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
file_header_cmp(struct file_header *f1, struct file_header *f2)
{

	if (f1 == f2)
		return (0);
	else {
		if (f1->fr == NULL) {
			return ((f2->fr == NULL) ? 0 : +1);
		} else if (f2->fr == NULL)
			return (-1);
		else {
			int ret;

			ret = list_coll(&(f1->si), &(f2->si));
			if (!ret)
				return ((f1->file_pos < f2->file_pos) ? -1 : +1);
			return (ret);
		}
	}
}