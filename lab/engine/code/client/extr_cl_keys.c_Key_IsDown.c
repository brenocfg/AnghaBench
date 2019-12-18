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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_2__ {int /*<<< orphan*/  down; } ;

/* Variables and functions */
 int MAX_KEYS ; 
 TYPE_1__* keys ; 
 int /*<<< orphan*/  qfalse ; 

qboolean Key_IsDown( int keynum ) {
	if ( keynum < 0 || keynum >= MAX_KEYS ) {
		return qfalse;
	}

	return keys[keynum].down;
}