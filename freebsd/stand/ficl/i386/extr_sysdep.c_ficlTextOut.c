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
typedef  int /*<<< orphan*/  FICL_VM ;

/* Variables and functions */
 int /*<<< orphan*/  IGNORE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (char) ; 

void  ficlTextOut(FICL_VM *pVM, char *msg, int fNewline)
{
    IGNORE(pVM);

    while(*msg != 0)
	putchar((unsigned char)*(msg++));
    if (fNewline)
	putchar('\n');

   return;
}