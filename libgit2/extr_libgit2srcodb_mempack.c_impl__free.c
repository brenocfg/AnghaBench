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
struct memory_packer_db {int /*<<< orphan*/  objects; } ;
typedef  int /*<<< orphan*/  git_odb_backend ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (struct memory_packer_db*) ; 
 int /*<<< orphan*/  git_mempack_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oidmap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void impl__free(git_odb_backend *_backend)
{
	struct memory_packer_db *db = (struct memory_packer_db *)_backend;

	git_mempack_reset(_backend);
	git_oidmap_free(db->objects);
	git__free(db);
}