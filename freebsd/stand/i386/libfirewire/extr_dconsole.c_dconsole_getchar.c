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
 int dcons_checkc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_poll () ; 
 int /*<<< orphan*/ * sc ; 

__attribute__((used)) static int
dconsole_getchar(void)
{
    fw_poll();
    return (dcons_checkc(&sc[0]));
}