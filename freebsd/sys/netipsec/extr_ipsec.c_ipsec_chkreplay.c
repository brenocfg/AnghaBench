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
typedef  int uint32_t ;
struct secreplay {int wsize; scalar_t__ count; int lastseq; int* bitmap; int /*<<< orphan*/  bitmap_size; } ;
struct secasvar {struct secreplay* replay; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int IPSEC_BITMAP_INDEX_MASK (int /*<<< orphan*/ ) ; 
 int IPSEC_BITMAP_LOC_MASK ; 
 int IPSEC_REDUNDANT_BIT_SHIFTS ; 

int
ipsec_chkreplay(uint32_t seq, struct secasvar *sav)
{
	const struct secreplay *replay;
	uint32_t wsizeb;		/* Constant: window size. */
	int index, bit_location;

	IPSEC_ASSERT(sav != NULL, ("Null SA"));
	IPSEC_ASSERT(sav->replay != NULL, ("Null replay state"));

	replay = sav->replay;

	/* No need to check replay if disabled. */
	if (replay->wsize == 0)
		return (1);

	/* Constant. */
	wsizeb = replay->wsize << 3;

	/* Sequence number of 0 is invalid. */
	if (seq == 0)
		return (0);

	/* First time is always okay. */
	if (replay->count == 0)
		return (1);

	/* Larger sequences are okay. */
	if (seq > replay->lastseq)
		return (1);

	/* Over range to check, i.e. too old or wrapped. */
	if (replay->lastseq - seq >= wsizeb)
		return (0);

	/* The sequence is inside the sliding window
	 * now check the bit in the bitmap
	 * bit location only depends on the sequence number
	 */
	bit_location = seq & IPSEC_BITMAP_LOC_MASK;
	index = (seq >> IPSEC_REDUNDANT_BIT_SHIFTS)
		& IPSEC_BITMAP_INDEX_MASK(replay->bitmap_size);

	/* This packet already seen? */
	if ((replay->bitmap)[index] & (1 << bit_location))
		return (0);
	return (1);
}