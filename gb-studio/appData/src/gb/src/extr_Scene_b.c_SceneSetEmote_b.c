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
typedef  int UWORD ;
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BUBBLE_SPRITE_LEFT ; 
 size_t EMOTES_SPRITE_BANK ; 
 int EMOTES_SPRITE_BANK_OFFSET ; 
 int /*<<< orphan*/  SetBankedSpriteData (size_t,int,int,int) ; 
 scalar_t__* bank_data_ptrs ; 
 scalar_t__ emote_actor ; 
 int emote_timer ; 
 int /*<<< orphan*/  hide_sprite_pair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_tile_pair (int /*<<< orphan*/ ,int,int) ; 

void SceneSetEmote_b(UBYTE actor, UBYTE type)
{
  UWORD scene_load_ptr;

  hide_sprite_pair(BUBBLE_SPRITE_LEFT);
  scene_load_ptr = ((UWORD)bank_data_ptrs[EMOTES_SPRITE_BANK]) + EMOTES_SPRITE_BANK_OFFSET;
  SetBankedSpriteData(EMOTES_SPRITE_BANK, 124, 4, scene_load_ptr + ((UWORD)type * 64));

  set_sprite_tile_pair(BUBBLE_SPRITE_LEFT, 124, 126);
  emote_timer = 1;
  emote_actor = actor;
}