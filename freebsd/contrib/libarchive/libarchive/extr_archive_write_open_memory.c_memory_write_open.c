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
struct write_memory_data {scalar_t__ used; scalar_t__* client_size; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int archive_write_get_bytes_in_last_block (struct archive*) ; 
 int /*<<< orphan*/  archive_write_set_bytes_in_last_block (struct archive*,int) ; 

__attribute__((used)) static int
memory_write_open(struct archive *a, void *client_data)
{
	struct write_memory_data *mine;
	mine = client_data;
	mine->used = 0;
	if (mine->client_size != NULL)
		*mine->client_size = mine->used;
	/* Disable padding if it hasn't been set explicitly. */
	if (-1 == archive_write_get_bytes_in_last_block(a))
		archive_write_set_bytes_in_last_block(a, 1);
	return (ARCHIVE_OK);
}