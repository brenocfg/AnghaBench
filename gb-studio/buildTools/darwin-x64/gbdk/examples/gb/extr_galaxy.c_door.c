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
 scalar_t__ CLOSED ; 
 scalar_t__ CLOSING ; 
 size_t NBDFRAMES ; 
 scalar_t__ OPENED ; 
 scalar_t__ OPENING ; 
 size_t doorpos ; 
 scalar_t__ doorstate ; 
 int /*<<< orphan*/ * film ; 
 int /*<<< orphan*/  set_win_tiles (int,int,int,int,int /*<<< orphan*/ ) ; 

void door()
{
  if(doorstate == OPENING) {
    doorpos++;
    /* Draw the door in the window */
    set_win_tiles(2, 2, 12, 6, film[doorpos]);
    if(doorpos == NBDFRAMES)
      doorstate = OPENED;
  } else if(doorstate == CLOSING) {
    doorpos--;
    /* Draw the door in the window */
    set_win_tiles(2, 2, 12, 6, film[doorpos]);
    if(doorpos == 0)
      doorstate = CLOSED;
  }
}