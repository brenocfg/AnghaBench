#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UWORD ;
typedef  size_t UBYTE ;
struct TYPE_4__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_5__ {int x; int y; } ;
struct TYPE_6__ {void* moving; TYPE_1__ pos; TYPE_2__ dir; } ;
typedef  int /*<<< orphan*/  POS ;

/* Variables and functions */
 scalar_t__ ACTOR_MAX_Y ; 
 int ACTOR_NOCLIP ; 
 size_t DIV_8 (scalar_t__) ; 
 void* FALSE ; 
 size_t SceneNpcAt_b (size_t,size_t,size_t) ; 
 int /*<<< orphan*/  SceneRenderActor_b (size_t) ; 
 void* TRUE ; 
 int actor_move_settings ; 
 TYPE_3__* actors ; 
 void* check_triggers ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int* scene_col_tiles ; 
 size_t scene_height ; 
 size_t scene_num_actors ; 
 size_t scene_width ; 
 scalar_t__ script_ptr ; 
 int /*<<< orphan*/  update_dir ; 

void SceneUpdateActorMovement_b(UBYTE i)
{
  UBYTE next_tx, next_ty;
  UBYTE npc;
  UWORD collision_index;

  memcpy(&actors[i].dir, update_dir, sizeof(POS));

  SceneRenderActor_b(i);

  // Dont check collisions when running script
  if (script_ptr != 0 && (actor_move_settings & ACTOR_NOCLIP))
  {
    if (i == 0)
    {
      check_triggers = TRUE;
    }
    actors[i].moving = TRUE;
    return;
  }

  next_tx = DIV_8(actors[i].pos.x) + actors[i].dir.x;
  next_ty = DIV_8(actors[i].pos.y) + actors[i].dir.y;

  // Check for npc collisions
  npc = SceneNpcAt_b(i, next_tx, next_ty);
  if (npc != scene_num_actors)
  {
    actors[i].moving = FALSE;
    return;
  }

  // Stop at left edge
  if (actors[i].dir.x == -1 && next_tx == 0)
  {
    actors[i].moving = FALSE;
    return;
  }

  // Stop at right edge
  if (actors[i].dir.x == 1 && next_tx == scene_width)
  {
    actors[i].moving = FALSE;
    return;
  }

  // Stop at top edge
  if (actors[i].dir.y == -1 && next_ty == 0)
  {
    actors[i].moving = FALSE;
    return;
  }

  // Stop at bottom edge
  if (actors[i].dir.y == 1 && (next_ty == (scene_height + 1) || actors[i].pos.y == ACTOR_MAX_Y))
  {
    actors[i].moving = FALSE;
    return;
  }

  // Check collisions on left tile
  collision_index = ((UWORD)scene_width * (next_ty - 1)) + (next_tx - 1);
  if (scene_col_tiles[collision_index >> 3] & (1 << (collision_index & 7)))
  {
    actors[i].moving = FALSE;
    return;
  }

  // Check collisions on right tile
  collision_index = ((UWORD)scene_width * (next_ty - 1)) + (next_tx - 1) + 1;
  if (scene_col_tiles[collision_index >> 3] & (1 << (collision_index & 7)))
  {
    actors[i].moving = FALSE;
    return;
  }

  if (i == 0)
  {
    check_triggers = TRUE;
  }
  actors[i].moving = TRUE;
}