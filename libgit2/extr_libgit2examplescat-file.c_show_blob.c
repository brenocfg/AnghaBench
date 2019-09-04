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
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_blob_rawsize (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void show_blob(const git_blob *blob)
{
	/* ? Does this need crlf filtering? */
	fwrite(git_blob_rawcontent(blob), (size_t)git_blob_rawsize(blob), 1, stdout);
}