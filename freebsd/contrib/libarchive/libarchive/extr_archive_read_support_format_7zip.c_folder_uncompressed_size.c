#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct _7z_folder {scalar_t__* unPackSize; TYPE_1__* bindPairs; int /*<<< orphan*/  numBindPairs; scalar_t__ numOutStreams; } ;
struct TYPE_2__ {scalar_t__ outIndex; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t
folder_uncompressed_size(struct _7z_folder *f)
{
	int n = (int)f->numOutStreams;
	unsigned pairs = (unsigned)f->numBindPairs;

	while (--n >= 0) {
		unsigned i;
		for (i = 0; i < pairs; i++) {
			if (f->bindPairs[i].outIndex == (uint64_t)n)
				break;
		}
		if (i >= pairs)
			return (f->unPackSize[n]);
	}
	return (0);
}