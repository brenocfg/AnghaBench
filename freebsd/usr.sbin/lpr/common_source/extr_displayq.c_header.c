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
 int /*<<< orphan*/  SIZCOL ; 
 int /*<<< orphan*/  blankfill (int /*<<< orphan*/ ) ; 
 scalar_t__ col ; 
 char* head0 ; 
 char* head1 ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void
header(void)
{
	printf("%s", head0);
	col = strlen(head0)+1;
	blankfill(SIZCOL);
	printf("%s", head1);
}