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
 scalar_t__ DEF_KS ; 
 int /*<<< orphan*/  DEF_KX ; 
 int /*<<< orphan*/  DEF_KY ; 
 int /*<<< orphan*/  DEF_SP ; 
 size_t MAX_KT ; 
 scalar_t__* kf ; 
 int /*<<< orphan*/ * kx ; 
 int /*<<< orphan*/ * ky ; 
 int /*<<< orphan*/  move_sprite (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_tile (scalar_t__,int /*<<< orphan*/ ) ; 

void init_kirai()
{
  UBYTE i;

  for( i=0; i<MAX_KT; i++ ) {
    kf[i] = 0;
    kx[i] = DEF_KX;
    ky[i] = DEF_KY;
    set_sprite_tile( i+DEF_KS, DEF_SP );
    move_sprite( i+DEF_KS, kx[i], ky[i] );
  }
}