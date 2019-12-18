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
struct fifolog_file {scalar_t__ fd; int /*<<< orphan*/ * recbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OBJ_NOTNULL (struct fifolog_file const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFOLOG_FILE_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
fifolog_int_file_assert(const struct fifolog_file *ff)
{

	CHECK_OBJ_NOTNULL(ff, FIFOLOG_FILE_MAGIC);
	assert(ff->fd >= 0);
	assert(ff->recbuf != NULL);
}