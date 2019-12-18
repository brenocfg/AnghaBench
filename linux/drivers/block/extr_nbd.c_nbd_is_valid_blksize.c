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

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 

__attribute__((used)) static bool nbd_is_valid_blksize(unsigned long blksize)
{
	if (!blksize || !is_power_of_2(blksize) || blksize < 512 ||
	    blksize > PAGE_SIZE)
		return false;
	return true;
}