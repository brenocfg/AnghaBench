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
typedef  int /*<<< orphan*/  git_writestream ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {TYPE_1__ source; } ;
typedef  TYPE_2__ git_filter_list ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 scalar_t__ buf_from_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_id (int /*<<< orphan*/ *) ; 
 int git_filter_list_stream_data (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_filter_list_stream_blob(
	git_filter_list *filters,
	git_blob *blob,
	git_writestream *target)
{
	git_buf in = GIT_BUF_INIT;

	if (buf_from_blob(&in, blob) < 0)
		return -1;

	if (filters)
		git_oid_cpy(&filters->source.oid, git_blob_id(blob));

	return git_filter_list_stream_data(filters, &in, target);
}