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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; scalar_t__ len; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_OBJECT_INVALID ; 
 int /*<<< orphan*/  git__calloc (int,int) ; 
 int /*<<< orphan*/  odb_hardcoded_type (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int odb_read_hardcoded(bool *found, git_rawobj *raw, const git_oid *id)
{
	git_object_t type;

	*found = false;

	if ((type = odb_hardcoded_type(id)) == GIT_OBJECT_INVALID)
		return 0;

	raw->type = type;
	raw->len = 0;
	raw->data = git__calloc(1, sizeof(uint8_t));
	GIT_ERROR_CHECK_ALLOC(raw->data);

	*found = true;
	return 0;
}