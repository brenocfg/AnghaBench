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
typedef  size_t u_int8_t ;

/* Variables and functions */
 size_t* ng_btsocket_rfcomm_crc_table ; 

__attribute__((used)) static u_int8_t
ng_btsocket_rfcomm_crc(u_int8_t *data, int length)
{
	u_int8_t	crc = 0xff;

	while (length --)
		crc = ng_btsocket_rfcomm_crc_table[crc ^ *data++];

	return (crc);
}