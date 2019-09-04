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
typedef  int /*<<< orphan*/  git_refdb_backend ;
struct TYPE_4__ {int /*<<< orphan*/ * backend; } ;
typedef  TYPE_1__ git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  refdb_free_backend (TYPE_1__*) ; 

int git_refdb_set_backend(git_refdb *db, git_refdb_backend *backend)
{
	refdb_free_backend(db);
	db->backend = backend;

	return 0;
}