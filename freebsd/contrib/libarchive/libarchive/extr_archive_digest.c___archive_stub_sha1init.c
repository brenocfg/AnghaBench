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
typedef  int /*<<< orphan*/  archive_sha1_ctx ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 

__attribute__((used)) static int
__archive_stub_sha1init(archive_sha1_ctx *ctx)
{
	(void)ctx; /* UNUSED */
	return (ARCHIVE_FAILED);
}