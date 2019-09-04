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
struct TYPE_3__ {int /*<<< orphan*/  blen; int /*<<< orphan*/  bytes; int /*<<< orphan*/  file; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ object_data ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  GIT_OBJECT_DIR_MODE ; 
 int S_IREAD ; 
 int S_IWRITE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_creat (int /*<<< orphan*/ ,int) ; 
 scalar_t__ p_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_object_files(object_data *d)
{
	int fd;

	if (p_mkdir(d->dir, GIT_OBJECT_DIR_MODE) < 0)
		cl_assert(errno == EEXIST);

	cl_assert((fd = p_creat(d->file, S_IREAD | S_IWRITE)) >= 0);
	cl_must_pass(p_write(fd, d->bytes, d->blen));

	p_close(fd);
}