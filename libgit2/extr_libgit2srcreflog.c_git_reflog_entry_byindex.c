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
typedef  int /*<<< orphan*/  git_reflog_entry ;
struct TYPE_6__ {size_t length; } ;
struct TYPE_5__ {TYPE_2__ entries; } ;
typedef  TYPE_1__ git_reflog ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  const* git_vector_get (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reflog_inverse_index (size_t,size_t) ; 

const git_reflog_entry * git_reflog_entry_byindex(const git_reflog *reflog, size_t idx)
{
	assert(reflog);

	if (idx >= reflog->entries.length)
		return NULL;

	return git_vector_get(
		&reflog->entries, reflog_inverse_index(idx, reflog->entries.length));
}