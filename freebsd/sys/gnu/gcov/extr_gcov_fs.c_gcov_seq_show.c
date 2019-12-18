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
struct seq_file {int /*<<< orphan*/  buf; } ;
struct gcov_iterator {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ gcov_iter_write (struct gcov_iterator*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gcov_seq_show(struct seq_file *seq, void *data)
{
	struct gcov_iterator *iter = data;

	if (gcov_iter_write(iter, seq->buf))
		return (-EINVAL);
	return (0);
}