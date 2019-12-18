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
struct read_file_data {scalar_t__ use_lseek; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_skip_lseek (struct archive*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
file_skip(struct archive *a, void *client_data, int64_t request)
{
	struct read_file_data *mine = (struct read_file_data *)client_data;

	/* Delegate skip requests. */
	if (mine->use_lseek)
		return (file_skip_lseek(a, client_data, request));

	/* If we can't skip, return 0; libarchive will read+discard instead. */
	return (0);
}