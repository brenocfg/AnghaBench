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
struct write_memory_data {size_t size; size_t* client_size; void* buff; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int archive_write_open (struct archive*,struct write_memory_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memory_write ; 
 int /*<<< orphan*/  memory_write_close ; 
 int /*<<< orphan*/  memory_write_open ; 

int
archive_write_open_memory(struct archive *a, void *buff, size_t buffSize, size_t *used)
{
	struct write_memory_data *mine;

	mine = (struct write_memory_data *)calloc(1, sizeof(*mine));
	if (mine == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	mine->buff = buff;
	mine->size = buffSize;
	mine->client_size = used;
	return (archive_write_open(a, mine,
		    memory_write_open, memory_write, memory_write_close));
}