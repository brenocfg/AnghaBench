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
struct spicds_info {int /*<<< orphan*/  devinfo; int /*<<< orphan*/  (* ctrl ) (int /*<<< orphan*/ ,unsigned int,int,unsigned int) ;scalar_t__ cif; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned int,int,unsigned int) ; 

__attribute__((used)) static void
spicds_wrbit(struct spicds_info *codec, int bit)
{
	unsigned int cs, cdti;
	if (codec->cif)
		cs = 1;
	else
		cs = 0;
	if (bit)
		cdti = 1;
	else
		cdti = 0;
	codec->ctrl(codec->devinfo, cs, 0, cdti);
	DELAY(1);
	codec->ctrl(codec->devinfo, cs, 1, cdti);
	DELAY(1);

	return;
}