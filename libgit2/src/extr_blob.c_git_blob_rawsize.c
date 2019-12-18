#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_off_t ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int /*<<< orphan*/  odb; TYPE_1__ raw; } ;
struct TYPE_8__ {TYPE_2__ data; scalar_t__ raw; } ;
typedef  TYPE_3__ git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  git_odb_object_size (int /*<<< orphan*/ ) ; 

git_off_t git_blob_rawsize(const git_blob *blob)
{
	assert(blob);
	if (blob->raw)
		return blob->data.raw.size;
	else
		return (git_off_t)git_odb_object_size(blob->data.odb);
}