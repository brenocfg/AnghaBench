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
typedef  scalar_t__ UBYTE ;
typedef  int /*<<< orphan*/  ACTOR ;

/* Variables and functions */
 int /*<<< orphan*/  ACTOR_ENABLED (scalar_t__*) ; 
 int /*<<< orphan*/  ACTOR_X (scalar_t__*) ; 
 int /*<<< orphan*/  ACTOR_Y (scalar_t__*) ; 
 scalar_t__ DIV_8 (int /*<<< orphan*/ ) ; 
 scalar_t__* actors ; 
 scalar_t__ scene_num_actors ; 

UBYTE SceneNpcAt_b(UBYTE index, UBYTE tx_a, UBYTE ty_a)
{
  UBYTE i, tx_b, ty_b, jump;
  UBYTE *ptr;

  ptr = actors;
  jump = sizeof(ACTOR);

  for (i = 0; i != scene_num_actors; i++)
  {
    if (i == index || !ACTOR_ENABLED(ptr))
    {
      ptr += jump;
      continue;
    }
    tx_b = DIV_8(ACTOR_X(ptr));
    ty_b = DIV_8(ACTOR_Y(ptr));
    if (ty_b == 0)
    {
      // If actor at posY=256 (really 0 since 8bit) convert to correct tile
      // since DIV_8 will give tile as 0 rather than 32
      ty_b = 32;
    }
    if ((ty_a == ty_b || ty_a == ty_b - 1) &&
        (tx_a == tx_b || tx_a == tx_b + 1 || tx_a + 1 == tx_b))
    {
      return i;
    }
    ptr += jump;
  }
  return scene_num_actors;
}