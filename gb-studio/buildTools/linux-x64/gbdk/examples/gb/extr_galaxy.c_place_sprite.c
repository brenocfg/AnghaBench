#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ h; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct TYPE_6__ {int /*<<< orphan*/  h; } ;
struct TYPE_7__ {TYPE_2__ b; } ;

/* Variables and functions */
 int /*<<< orphan*/  move_sprite (int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_4__ sposx ; 
 TYPE_3__ sposy ; 

void place_sprite()
{
  move_sprite(0, sposx.b.h, sposy.b.h);
  move_sprite(1, sposx.b.h+8, sposy.b.h);
}