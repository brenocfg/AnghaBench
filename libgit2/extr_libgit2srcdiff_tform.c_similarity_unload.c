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
struct TYPE_3__ {int /*<<< orphan*/  data; scalar_t__ blob; scalar_t__ odb_obj; } ;
typedef  TYPE_1__ similarity_info ;

/* Variables and functions */
 int /*<<< orphan*/  git_blob_free (scalar_t__) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_object_free (scalar_t__) ; 

__attribute__((used)) static void similarity_unload(similarity_info *info)
{
	if (info->odb_obj)
		git_odb_object_free(info->odb_obj);

	if (info->blob)
		git_blob_free(info->blob);
	else
		git_buf_dispose(&info->data);
}