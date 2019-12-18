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
struct seq_file {void* private; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ gcov_iter_next (void*) ; 
 int /*<<< orphan*/  gcov_iter_start (void*) ; 

__attribute__((used)) static void *
gcov_seq_start(struct seq_file *seq, off_t *pos)
{
	off_t i;

	gcov_iter_start(seq->private);
	for (i = 0; i < *pos; i++) {
		if (gcov_iter_next(seq->private))
			return NULL;
	}
	return seq->private;
}