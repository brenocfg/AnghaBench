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
 unsigned short IEEE80211_SEQ_SEQ_SHIFT ; 
 int /*<<< orphan*/  assert (int) ; 

short seqfn(unsigned short seq, unsigned short fn)
{
	unsigned short r = 0;

	assert(fn < 16);

	r = fn;
	r |=  ( (seq % 4096) << IEEE80211_SEQ_SEQ_SHIFT);
	return r;
}