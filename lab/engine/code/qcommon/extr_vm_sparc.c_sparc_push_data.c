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
struct func_info {int data_num; struct data_hunk* data_first; } ;
struct data_hunk {int count; unsigned int* data; struct data_hunk* next; } ;

/* Variables and functions */
 scalar_t__ HUNK_SIZE ; 
 unsigned int VM_Data_Offset (int /*<<< orphan*/ ) ; 
 struct data_hunk* Z_Malloc (int) ; 
 int /*<<< orphan*/ * data ; 

__attribute__((used)) static unsigned int sparc_push_data(struct func_info * const fp, unsigned int val)
{
	struct data_hunk *last, *dp = fp->data_first;
	int off = 0;

	last = NULL;
	while (dp) {
		int i;

		for (i = 0; i < dp->count; i++) {
			if (dp->data[i] == val) {
				off += i;
				return VM_Data_Offset(data[off]);
			}
		}
		off += dp->count;
		last = dp;
		dp = dp->next;
	}

	dp = last;
	if (!dp || dp->count >= HUNK_SIZE) {
		struct data_hunk *new = Z_Malloc(sizeof(*new));
		if (!dp)
			fp->data_first = new;
		else
			dp->next = new;
		dp = new;
		dp->count = 0;
		dp->next = NULL;
	}
	dp->data[dp->count++] = val;
	fp->data_num = off + 1;
	return VM_Data_Offset(data[off]);
}