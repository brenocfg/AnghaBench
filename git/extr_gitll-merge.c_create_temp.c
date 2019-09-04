#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ mmfile_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xmkstemp (char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,size_t,char*) ; 

__attribute__((used)) static void create_temp(mmfile_t *src, char *path, size_t len)
{
	int fd;

	xsnprintf(path, len, ".merge_file_XXXXXX");
	fd = xmkstemp(path);
	if (write_in_full(fd, src->ptr, src->size) < 0)
		die_errno("unable to write temp-file");
	close(fd);
}