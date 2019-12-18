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
struct preloaded_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODINFOMD_SMAP ; 
 int /*<<< orphan*/  MODINFOMD_SMAP_XATTR ; 
 int /*<<< orphan*/  file_addmetadata (struct preloaded_file*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smapattr ; 
 int /*<<< orphan*/ * smapbase ; 
 int smaplen ; 

void
bios_addsmapdata(struct preloaded_file *kfp)
{
	size_t			size;

	if (smapbase == NULL || smaplen == 0)
		return;
	size = smaplen * sizeof(*smapbase);
	file_addmetadata(kfp, MODINFOMD_SMAP, size, smapbase);
	if (smapattr != NULL) {
		size = smaplen * sizeof(*smapattr);
		file_addmetadata(kfp, MODINFOMD_SMAP_XATTR, size, smapattr);
	}
}