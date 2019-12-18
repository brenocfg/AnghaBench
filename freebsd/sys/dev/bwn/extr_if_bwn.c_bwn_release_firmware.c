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
struct TYPE_2__ {int /*<<< orphan*/  initvals_band; int /*<<< orphan*/  initvals; int /*<<< orphan*/  pcm; int /*<<< orphan*/  ucode; } ;
struct bwn_mac {TYPE_1__ mac_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_do_release_fw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwn_release_firmware(struct bwn_mac *mac)
{

	bwn_do_release_fw(&mac->mac_fw.ucode);
	bwn_do_release_fw(&mac->mac_fw.pcm);
	bwn_do_release_fw(&mac->mac_fw.initvals);
	bwn_do_release_fw(&mac->mac_fw.initvals_band);
}