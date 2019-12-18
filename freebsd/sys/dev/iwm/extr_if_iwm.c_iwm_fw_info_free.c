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
struct iwm_fw_info {int /*<<< orphan*/  img; int /*<<< orphan*/ * fw_fp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  firmware_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
iwm_fw_info_free(struct iwm_fw_info *fw)
{
	firmware_put(fw->fw_fp, FIRMWARE_UNLOAD);
	fw->fw_fp = NULL;
	memset(fw->img, 0, sizeof(fw->img));
}