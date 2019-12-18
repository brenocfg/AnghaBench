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
typedef  int u8 ;

/* Variables and functions */
 int AUTO_INC ; 
 int CURSOR_FOLLOWS_DISP ; 
 int ENTRYMODE_CMD ; 
 int /*<<< orphan*/  MODE_INST ; 
 int /*<<< orphan*/  pvc_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvc_entrymode(u8 cmd)
{
	pvc_write(ENTRYMODE_CMD | (cmd & (AUTO_INC|CURSOR_FOLLOWS_DISP)),
		  MODE_INST);
}