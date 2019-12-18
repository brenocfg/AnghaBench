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
struct _7z_folder {unsigned int numCoders; TYPE_1__* unPackSize; TYPE_1__* packedStreams; TYPE_1__* bindPairs; TYPE_1__* coders; } ;
struct TYPE_2__ {struct TYPE_2__* properties; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
free_Folder(struct _7z_folder *f)
{
	unsigned i;

	if (f->coders) {
		for (i = 0; i< f->numCoders; i++) {
			free(f->coders[i].properties);
		}
		free(f->coders);
	}
	free(f->bindPairs);
	free(f->packedStreams);
	free(f->unPackSize);
}