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
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  move_sprite (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_prop (int,int /*<<< orphan*/ ) ; 

void SpritesReset()
{
  UBYTE i;

  for (i = 0; i != 40; i++) {
    move_sprite(i, 0, 0);
    set_sprite_prop(i, 0);
  }
}