#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t len; int /*<<< orphan*/  type; void* data; } ;
typedef  TYPE_1__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int git_odb__hashobj (int /*<<< orphan*/ *,TYPE_1__*) ; 

int git_odb_hash(git_oid *id, const void *data, size_t len, git_object_t type)
{
	git_rawobj raw;

	assert(id);

	raw.data = (void *)data;
	raw.len = len;
	raw.type = type;

	return git_odb__hashobj(id, &raw);
}