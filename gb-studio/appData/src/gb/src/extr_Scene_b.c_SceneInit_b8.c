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
 int /*<<< orphan*/  ReadBankedUBYTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  col_bank ; 
 size_t collision_tiles_len ; 
 int /*<<< orphan*/ * scene_col_tiles ; 
 int /*<<< orphan*/  scene_load_col_ptr ; 

void SceneInit_b8()
{
  UBYTE i;

  // Load collisions ( bitwise ceil by adding the divisor minus one to the dividend )
  for (i = 0; i != collision_tiles_len; i++)
  {
    scene_col_tiles[i] = ReadBankedUBYTE(col_bank, scene_load_col_ptr);
    scene_load_col_ptr++;
  }
}