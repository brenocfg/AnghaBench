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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int rawsum_t ;

/* Variables and functions */
 int /*<<< orphan*/  htobe16 (int) ; 

uint16_t
nm_os_csum_fold(rawsum_t cur_sum)
{
	/* TODO XXX please use the FreeBSD implementation for this. */
	while (cur_sum >> 16)
		cur_sum = (cur_sum & 0xFFFF) + (cur_sum >> 16);

	return htobe16((~cur_sum) & 0xFFFF);
}