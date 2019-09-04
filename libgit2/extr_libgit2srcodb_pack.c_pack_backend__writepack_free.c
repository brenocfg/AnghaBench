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
struct pack_writepack {int /*<<< orphan*/  indexer; } ;
struct git_odb_writepack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct pack_writepack*) ; 
 int /*<<< orphan*/  git__free (struct pack_writepack*) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pack_backend__writepack_free(struct git_odb_writepack *_writepack)
{
	struct pack_writepack *writepack = (struct pack_writepack *)_writepack;

	assert(writepack);

	git_indexer_free(writepack->indexer);
	git__free(writepack);
}