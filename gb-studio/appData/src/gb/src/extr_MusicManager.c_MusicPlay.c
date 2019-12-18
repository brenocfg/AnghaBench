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
typedef  size_t UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PTRS_BANK ; 
 int /*<<< orphan*/  POP_BANK ; 
 int /*<<< orphan*/  PUSH_BANK (size_t) ; 
 size_t ReadBankedUBYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t current_index ; 
 int /*<<< orphan*/  gbt_loop (size_t) ; 
 int /*<<< orphan*/  gbt_play (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/ * music_banks ; 
 int /*<<< orphan*/ * music_tracks ; 

void MusicPlay(UBYTE index, UBYTE loop, UBYTE return_bank)
{
  UBYTE music_bank;

  if (index != current_index)
  {
    current_index = index;
    music_bank = ReadBankedUBYTE(DATA_PTRS_BANK, &music_banks[index]);

    PUSH_BANK(return_bank);
    gbt_play(music_tracks[index], music_bank, 7);
    gbt_loop(loop);

    POP_BANK;
  }
}