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
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void blob_parsing(git_repository *repo)
{
	git_blob *blob;
	git_oid oid;

	printf("\n*Blob Parsing*\n");

	git_oid_fromstr(&oid, "1385f264afb75a56a5bec74243be9b367ba4ca08");
	git_blob_lookup(&blob, repo, &oid);

	/**
	 * You can access a buffer with the raw contents of the blob directly.
	 * Note that this buffer may not be contain ASCII data for certain blobs
	 * (e.g. binary files): do not consider the buffer a NULL-terminated
	 * string, and use the `git_blob_rawsize` attribute to find out its exact
	 * size in bytes
	 * */
	printf("Blob Size: %ld\n", (long)git_blob_rawsize(blob)); /* 8 */
	git_blob_rawcontent(blob); /* "content" */

	/**
	 * Free the blob after usage.
	 */
	git_blob_free(blob);
}