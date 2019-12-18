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
 int /*<<< orphan*/  msg_start ; 
 int /*<<< orphan*/  set_bkg_tiles (int,int,int,int,int /*<<< orphan*/ ) ; 

void hide_msg()
{
  set_bkg_tiles(  6, 9, 8, 1, msg_start );
}