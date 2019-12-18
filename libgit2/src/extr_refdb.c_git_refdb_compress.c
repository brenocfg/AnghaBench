#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* backend; } ;
typedef  TYPE_1__ git_refdb ;
struct TYPE_6__ {int (* compress ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int stub1 (TYPE_2__*) ; 

int git_refdb_compress(git_refdb *db)
{
	assert(db);

	if (db->backend->compress)
		return db->backend->compress(db->backend);

	return 0;
}