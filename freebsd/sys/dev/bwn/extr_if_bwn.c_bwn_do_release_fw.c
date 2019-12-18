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
struct bwn_fwfile {int /*<<< orphan*/ * filename; int /*<<< orphan*/ * fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  firmware_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_do_release_fw(struct bwn_fwfile *bfw)
{

	if (bfw->fw != NULL)
		firmware_put(bfw->fw, FIRMWARE_UNLOAD);
	bfw->fw = NULL;
	bfw->filename = NULL;
}