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
struct io_thread_req {int cow_offset; int /*<<< orphan*/  bitmap_words; int /*<<< orphan*/ * fds; } ;

/* Variables and functions */
 int map_error (int) ; 
 int os_pwrite_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int update_bitmap(struct io_thread_req *req)
{
	int n;

	if(req->cow_offset == -1)
		return map_error(0);

	n = os_pwrite_file(req->fds[1], &req->bitmap_words,
			  sizeof(req->bitmap_words), req->cow_offset);
	if (n != sizeof(req->bitmap_words))
		return map_error(-n);

	return map_error(0);
}