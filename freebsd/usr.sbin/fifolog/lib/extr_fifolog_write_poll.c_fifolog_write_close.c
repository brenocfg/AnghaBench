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
typedef  int /*<<< orphan*/  time_t ;
struct fifolog_writer {int cleanup; int /*<<< orphan*/  ff; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OBJ_NOTNULL (struct fifolog_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFOLOG_WRITER_MAGIC ; 
 int /*<<< orphan*/  fifolog_int_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifolog_write_assert (struct fifolog_writer*) ; 
 int /*<<< orphan*/  fifolog_write_gzip (struct fifolog_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void
fifolog_write_close(struct fifolog_writer *f)
{
	time_t now;

	CHECK_OBJ_NOTNULL(f, FIFOLOG_WRITER_MAGIC);
	fifolog_write_assert(f);

	f->cleanup = 1;
	time(&now);
	fifolog_write_gzip(f, now);
	fifolog_write_assert(f);
	fifolog_int_close(&f->ff);
	free(f->ff);
}