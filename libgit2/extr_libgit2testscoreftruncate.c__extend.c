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
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ git_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  fd ; 
 int p_fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int p_ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _extend(git_off_t i64len)
{
	struct stat st;
	int error;

	cl_assert((error = p_ftruncate(fd, i64len)) == 0);
	cl_assert((error = p_fstat(fd, &st)) == 0);
	cl_assert(st.st_size == i64len);
}