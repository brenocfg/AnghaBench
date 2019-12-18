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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 scalar_t__ CGB_TYPE ; 
 scalar_t__ _cpu ; 
 int /*<<< orphan*/  set_sprite_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void set_sprite_attrb( UBYTE nb, UBYTE tile )
{
  if( _cpu==CGB_TYPE ) {
    set_sprite_prop( nb, tile );
  }
}