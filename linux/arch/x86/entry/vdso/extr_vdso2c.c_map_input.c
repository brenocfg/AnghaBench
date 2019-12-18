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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void map_input(const char *name, void **addr, size_t *len, int prot)
{
	off_t tmp_len;

	int fd = open(name, O_RDONLY);
	if (fd == -1)
		err(1, "%s", name);

	tmp_len = lseek(fd, 0, SEEK_END);
	if (tmp_len == (off_t)-1)
		err(1, "lseek");
	*len = (size_t)tmp_len;

	*addr = mmap(NULL, tmp_len, prot, MAP_PRIVATE, fd, 0);
	if (*addr == MAP_FAILED)
		err(1, "mmap");

	close(fd);
}