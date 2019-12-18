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
 int /*<<< orphan*/  reply (int,char*) ; 
 scalar_t__ transflag ; 

void abor(void)
{
    if (!transflag)
	return;
    reply(426, "Transfer aborted. Data connection closed.");
    reply(226, "Abort successful");
    transflag = 0;
}