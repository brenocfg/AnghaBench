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
typedef  int /*<<< orphan*/  git_writestream ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_blob_create_from_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

int git_blob_create_fromstream(
    git_writestream **out,
    git_repository *repo,
    const char *hintpath)
{
	return  git_blob_create_from_stream(out, repo, hintpath);
}