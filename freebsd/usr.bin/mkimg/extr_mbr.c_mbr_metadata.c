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
typedef  scalar_t__ u_int ;
typedef  int lba_t ;

/* Variables and functions */
 scalar_t__ SCHEME_META_IMG_START ; 
 int round_track (int) ; 

__attribute__((used)) static lba_t
mbr_metadata(u_int where, lba_t blk)
{

	blk += (where == SCHEME_META_IMG_START) ? 1 : 0;
	return (round_track(blk));
}