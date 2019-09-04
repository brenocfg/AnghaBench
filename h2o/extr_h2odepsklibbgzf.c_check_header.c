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
typedef  int uint8_t ;

/* Variables and functions */
 int unpackInt16 (int*) ; 

__attribute__((used)) static int check_header(const uint8_t *header)
{
	return (header[0] == 31 && header[1] == 139 && header[2] == 8 && (header[3] & 4) != 0
			&& unpackInt16((uint8_t*)&header[10]) == 6
			&& header[12] == 'B' && header[13] == 'C'
			&& unpackInt16((uint8_t*)&header[14]) == 2);
}