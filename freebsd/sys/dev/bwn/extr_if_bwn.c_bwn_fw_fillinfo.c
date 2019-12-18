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
 int /*<<< orphan*/  BWN_FWTYPE_DEFAULT ; 
 int /*<<< orphan*/  BWN_FWTYPE_OPENSOURCE ; 
 int bwn_fw_gets (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_fw_fillinfo(struct bwn_mac *mac)
{
	int error;

	error = bwn_fw_gets(mac, BWN_FWTYPE_DEFAULT);
	if (error == 0)
		return (0);
	error = bwn_fw_gets(mac, BWN_FWTYPE_OPENSOURCE);
	if (error == 0)
		return (0);
	return (error);
}