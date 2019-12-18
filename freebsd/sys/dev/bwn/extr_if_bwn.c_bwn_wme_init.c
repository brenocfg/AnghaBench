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
 int BWN_HF_EDCF ; 
 int /*<<< orphan*/  BWN_IFSCTL ; 
 int BWN_IFSCTL_USE_EDCF ; 
 int BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int bwn_hf_read (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_hf_write (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_wme_load (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_wme_init(struct bwn_mac *mac)
{

	bwn_wme_load(mac);

	/* enable WME support. */
	bwn_hf_write(mac, bwn_hf_read(mac) | BWN_HF_EDCF);
	BWN_WRITE_2(mac, BWN_IFSCTL, BWN_READ_2(mac, BWN_IFSCTL) |
	    BWN_IFSCTL_USE_EDCF);
}