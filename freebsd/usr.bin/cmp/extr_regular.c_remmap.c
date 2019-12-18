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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MADV_SEQUENTIAL ; 
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MMAP_CHUNK ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  madvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char *
remmap(u_char *mem, int fd, off_t offset)
{
	if (mem != NULL)
		munmap(mem, MMAP_CHUNK);
	mem = mmap(NULL, MMAP_CHUNK, PROT_READ, MAP_SHARED, fd, offset);
	if (mem == MAP_FAILED)
		return (NULL);
	madvise(mem, MMAP_CHUNK, MADV_SEQUENTIAL);
	return (mem);
}