#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UBYTE ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRST_X ; 
 scalar_t__ FIRST_Y ; 
 scalar_t__ TITLE_Y ; 
 int /*<<< orphan*/  UNSIGNED ; 
 int /*<<< orphan*/  VAL_X ; 
 int /*<<< orphan*/  cls () ; 
 int /*<<< orphan*/  current_value (int,int) ; 
 int /*<<< orphan*/  gotoxy (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* params ; 
 int /*<<< orphan*/  print (scalar_t__) ; 
 int /*<<< orphan*/  println (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

UBYTE draw_screen(UBYTE mode)
{
  UBYTE i;

  cls();
  gotoxy(FIRST_X, TITLE_Y);
  print(params[0].name);

  for(i = 0; params[i+1].name; i++) {
    gotoxy(FIRST_X, FIRST_Y+i);
    print(params[i+1].name);
    gotoxy(VAL_X, FIRST_Y+i);
    println(current_value(mode, i), 10, UNSIGNED);
  }
  return i-1;
}