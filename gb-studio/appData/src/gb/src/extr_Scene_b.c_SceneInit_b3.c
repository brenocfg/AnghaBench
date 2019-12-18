#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_1__ dir; TYPE_2__ pos; int /*<<< orphan*/  moving; int /*<<< orphan*/  enabled; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__* actors ; 
 TYPE_4__ map_next_dir ; 
 TYPE_3__ map_next_pos ; 

void SceneInit_b3()
{
  // Init player
  actors[0].enabled = TRUE;
  actors[0].moving = FALSE;
  actors[0].pos.x = map_next_pos.x;
  actors[0].pos.y = map_next_pos.y;
  actors[0].dir.x = map_next_dir.x;
  actors[0].dir.y = map_next_dir.y;
}