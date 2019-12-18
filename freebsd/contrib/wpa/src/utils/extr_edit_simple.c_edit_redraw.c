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
 char* cmdbuf ; 
 size_t cmdbuf_pos ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void edit_redraw(void)
{
	cmdbuf[cmdbuf_pos] = '\0';
	printf("\r> %s", cmdbuf);
}