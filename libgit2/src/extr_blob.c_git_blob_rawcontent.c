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
struct TYPE_6__ {void const* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  odb; TYPE_1__ raw; } ;
struct TYPE_8__ {TYPE_2__ data; scalar_t__ raw; } ;
typedef  TYPE_3__ git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__ const*) ; 
 void const* git_odb_object_data (int /*<<< orphan*/ ) ; 

const void *git_blob_rawcontent(const git_blob *blob)
{
	assert(blob);
	if (blob->raw)
		return blob->data.raw.data;
	else
		return git_odb_object_data(blob->data.odb);
}