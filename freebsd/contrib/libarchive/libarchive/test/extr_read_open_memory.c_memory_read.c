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
struct read_memory_data {size_t end; size_t p; size_t read_size; void* copy_buff; int copy_buff_offset; int /*<<< orphan*/  copy_buff_size; } ;
struct archive {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
memory_read(struct archive *a, void *client_data, const void **buff)
{
	struct read_memory_data *mine = (struct read_memory_data *)client_data;
	ssize_t size;

	(void)a; /* UNUSED */
	size = mine->end - mine->p;
	if (size < 0) {
		buff = NULL;
		return 0;
	}
	if ((size_t)size > mine->read_size)
		size = mine->read_size;
	else
		memset(mine->copy_buff, 0xA5, mine->copy_buff_size);
	memcpy(mine->copy_buff + mine->copy_buff_offset, mine->p, size);
	*buff = mine->copy_buff + mine->copy_buff_offset;

        mine->p += size;
	return ((ssize_t)size);
}