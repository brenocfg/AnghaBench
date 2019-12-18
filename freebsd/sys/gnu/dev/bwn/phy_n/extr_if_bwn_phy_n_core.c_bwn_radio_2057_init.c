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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_radio_2057_init_post (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_radio_2057_init_pre (struct bwn_mac*) ; 
 int /*<<< orphan*/  r2057_upload_inittabs (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_radio_2057_init(struct bwn_mac *mac)
{
	bwn_radio_2057_init_pre(mac);
	r2057_upload_inittabs(mac);
	bwn_radio_2057_init_post(mac);
}