#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* next ) (TYPE_2__**,TYPE_1__*) ;int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ git_reference_iterator ;
struct TYPE_8__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__**,TYPE_1__*) ; 

int git_refdb_iterator_next(git_reference **out, git_reference_iterator *iter)
{
	int error;

	if ((error = iter->next(out, iter)) < 0)
		return error;

	GIT_REFCOUNT_INC(iter->db);
	(*out)->db = iter->db;

	return 0;
}