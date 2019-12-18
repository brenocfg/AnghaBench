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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mad_decode_field (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  thresholds ; 

__attribute__((used)) static int exceeds_threshold(int field, unsigned val)
{
	uint32_t thres = 0;
	mad_decode_field(thresholds, field, &thres);
	return (val > thres);
}