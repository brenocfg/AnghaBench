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
 int /*<<< orphan*/  GC_LOCK_ASSERT () ; 
 char buffer_data ; 
 scalar_t__ buffer_valid ; 
 int /*<<< orphan*/  gxemul_cons_readable () ; 

__attribute__((used)) static char
gxemul_cons_read(void)
{

	GC_LOCK_ASSERT();

	while (!gxemul_cons_readable());
	buffer_valid = 0;
	return (buffer_data);
}