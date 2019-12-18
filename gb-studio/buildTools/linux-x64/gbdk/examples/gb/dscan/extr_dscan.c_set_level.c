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
 int rnd_enemy ; 
 int rnd_kirai ; 

void set_level( UBYTE i )
{
  /* level */
  if( i < 9 ) {
    rnd_enemy = 100-(i*12); /*  1% - */
    rnd_kirai = 50-(i*6);   /*  2% - */
  } else {
    rnd_enemy = 0;      /* 100 % */
    rnd_kirai = 0;      /* 100 % */
  }
}