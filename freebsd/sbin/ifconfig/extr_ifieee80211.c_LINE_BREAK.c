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
 int col ; 
 int /*<<< orphan*/  printf (char*) ; 
 char spacer ; 

__attribute__((used)) static void
LINE_BREAK(void)
{
	if (spacer != '\t') {
		printf("\n");
		spacer = '\t';
	}
	col = 8;		/* 8-col tab */
}