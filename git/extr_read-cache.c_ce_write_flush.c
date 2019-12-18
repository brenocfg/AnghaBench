#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_hash_ctx ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  write_buffer ; 
 unsigned int write_buffer_len ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ce_write_flush(git_hash_ctx *context, int fd)
{
	unsigned int buffered = write_buffer_len;
	if (buffered) {
		the_hash_algo->update_fn(context, write_buffer, buffered);
		if (write_in_full(fd, write_buffer, buffered) < 0)
			return -1;
		write_buffer_len = 0;
	}
	return 0;
}