#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* read ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*) ;} ;
typedef  TYPE_1__ git_reader ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_filemode_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 

int git_reader_read(
	git_buf *out,
	git_oid *out_id,
	git_filemode_t *out_filemode,
	git_reader *reader,
	const char *filename)
{
	assert(out && reader && filename);

	return reader->read(out, out_id, out_filemode, reader, filename);
}