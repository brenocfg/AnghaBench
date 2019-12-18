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
struct bwi_mac {int /*<<< orphan*/ * mac_stub; int /*<<< orphan*/ * mac_iv_ext; int /*<<< orphan*/ * mac_iv; int /*<<< orphan*/ * mac_pcm; int /*<<< orphan*/ * mac_ucode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  firmware_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_mac_fw_free(struct bwi_mac *mac)
{
	if (mac->mac_ucode != NULL) {
		firmware_put(mac->mac_ucode, FIRMWARE_UNLOAD);
		mac->mac_ucode = NULL;
	}

	if (mac->mac_pcm != NULL) {
		firmware_put(mac->mac_pcm, FIRMWARE_UNLOAD);
		mac->mac_pcm = NULL;
	}

	if (mac->mac_iv != NULL) {
		firmware_put(mac->mac_iv, FIRMWARE_UNLOAD);
		mac->mac_iv = NULL;
	}

	if (mac->mac_iv_ext != NULL) {
		firmware_put(mac->mac_iv_ext, FIRMWARE_UNLOAD);
		mac->mac_iv_ext = NULL;
	}

	if (mac->mac_stub != NULL) {
		firmware_put(mac->mac_stub, FIRMWARE_UNLOAD);
		mac->mac_stub = NULL;
	}
}