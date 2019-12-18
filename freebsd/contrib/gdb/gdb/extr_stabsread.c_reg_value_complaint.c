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
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int,int,char const*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static void
reg_value_complaint (int arg1, int arg2, const char *arg3)
{
  complaint (&symfile_complaints,
	     "register number %d too large (max %d) in symbol %s", arg1, arg2,
	     arg3);
}