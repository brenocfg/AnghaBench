#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int git_blob_create_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t) ; 

int git_blob_create_frombuffer(
	git_oid *id, git_repository *repo, const void *buffer, size_t len)
{
	return git_blob_create_from_buffer(id, repo, buffer, len);
}