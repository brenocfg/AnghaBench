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
 int /*<<< orphan*/  GDT_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GDT_D_TIMEOUT ; 
 int /*<<< orphan*/  gccb ; 

__attribute__((used)) static void     
iir_timeout(void *arg)
{
    GDT_DPRINTF(GDT_D_TIMEOUT, ("iir_timeout(%p)\n", gccb));
}