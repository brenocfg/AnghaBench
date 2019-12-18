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
struct TYPE_2__ {int /*<<< orphan*/  fp; scalar_t__ pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  Fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pclose (int /*<<< orphan*/ ) ; 
 TYPE_1__* fp_head ; 

void
close_all_files(void)
{

	while (fp_head != NULL)
		if (fp_head->pipe)
			(void)Pclose(fp_head->fp);
		else
			(void)Fclose(fp_head->fp);
}