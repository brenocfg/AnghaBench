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
 int /*<<< orphan*/  gxemul_cons_data_write (char) ; 
 int /*<<< orphan*/  gxemul_cons_writable () ; 

__attribute__((used)) static void
gxemul_cons_write(char ch)
{

	GC_LOCK_ASSERT();

	while (!gxemul_cons_writable());
	gxemul_cons_data_write(ch);
}