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
struct write_memory_data {scalar_t__ used; scalar_t__ size; scalar_t__ buff; scalar_t__* client_size; } ;
struct archive {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 

__attribute__((used)) static ssize_t
memory_write(struct archive *a, void *client_data, const void *buff, size_t length)
{
	struct write_memory_data *mine;
	mine = client_data;

	if (mine->used + length > mine->size) {
		archive_set_error(a, ENOMEM, "Buffer exhausted");
		return (ARCHIVE_FATAL);
	}
	memcpy(mine->buff + mine->used, buff, length);
	mine->used += length;
	if (mine->client_size != NULL)
		*mine->client_size = mine->used;
	return (length);
}