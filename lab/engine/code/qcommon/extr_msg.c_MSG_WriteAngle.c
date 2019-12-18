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
 int /*<<< orphan*/  MSG_WriteByte (int /*<<< orphan*/ *,int) ; 

void MSG_WriteAngle( msg_t *sb, float f ) {
	MSG_WriteByte (sb, (int)(f*256/360) & 255);
}