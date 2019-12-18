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
struct file_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ file_header_cmp (struct file_header*,struct file_header*) ; 
 int /*<<< orphan*/  file_header_swap (struct file_header**,size_t,size_t) ; 

__attribute__((used)) static void
file_header_heap_sink(struct file_header **fh, size_t indx, size_t size)
{
	size_t left_child_index;
	size_t right_child_index;

	left_child_index = indx + indx + 1;
	right_child_index = left_child_index + 1;

	if (left_child_index < size) {
		size_t min_child_index;

		min_child_index = left_child_index;

		if ((right_child_index < size) &&
		    (file_header_cmp(fh[left_child_index],
		    fh[right_child_index]) > 0))
			min_child_index = right_child_index;
		if (file_header_cmp(fh[indx], fh[min_child_index]) > 0) {
			file_header_swap(fh, indx, min_child_index);
			file_header_heap_sink(fh, min_child_index, size);
		}
	}
}