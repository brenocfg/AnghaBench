#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {scalar_t__ compute_digest; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  flush_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ verify_last_error (TYPE_1__*) ; 

int git_filebuf_hash(git_oid *oid, git_filebuf *file)
{
	assert(oid && file && file->compute_digest);

	flush_buffer(file);

	if (verify_last_error(file) < 0)
		return -1;

	git_hash_final(oid, &file->digest);
	git_hash_ctx_cleanup(&file->digest);
	file->compute_digest = 0;

	return 0;
}