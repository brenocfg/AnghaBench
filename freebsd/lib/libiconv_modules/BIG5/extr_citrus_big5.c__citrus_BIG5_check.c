#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* cell; } ;
typedef  TYPE_1__ _BIG5EncodingInfo ;

/* Variables and functions */

__attribute__((used)) static __inline int
_citrus_BIG5_check(_BIG5EncodingInfo *ei, unsigned int c)
{

	return ((ei->cell[c & 0xFF] & 0x1) ? 2 : 1);
}