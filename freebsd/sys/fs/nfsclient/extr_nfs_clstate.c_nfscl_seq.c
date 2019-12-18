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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
nfscl_seq(uint32_t seqid1, uint32_t seqid2)
{

	if (seqid2 > seqid1 && (seqid2 - seqid1) >= 0x7fffffff)
		/* seqid2 has wrapped around. */
		return (0);
	if (seqid1 > seqid2 && (seqid1 - seqid2) >= 0x7fffffff)
		/* seqid1 has wrapped around. */
		return (1);
	if (seqid1 <= seqid2)
		return (1);
	return (0);
}