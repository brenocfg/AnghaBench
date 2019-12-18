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
struct _7z_substream_info {int /*<<< orphan*/  digests; int /*<<< orphan*/  digestsDefined; int /*<<< orphan*/  unpackSizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_SubStreamsInfo(struct _7z_substream_info *ss)
{
	free(ss->unpackSizes);
	free(ss->digestsDefined);
	free(ss->digests);
}