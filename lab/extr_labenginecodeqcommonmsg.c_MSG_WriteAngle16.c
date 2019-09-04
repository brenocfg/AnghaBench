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
typedef  int /*<<< orphan*/  msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANGLE2SHORT (float) ; 
 int /*<<< orphan*/  MSG_WriteShort (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void MSG_WriteAngle16( msg_t *sb, float f ) {
	MSG_WriteShort (sb, ANGLE2SHORT(f));
}