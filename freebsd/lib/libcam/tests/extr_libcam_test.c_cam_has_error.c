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
 int /*<<< orphan*/  cam_errbuf ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cam_has_error(void)
{

	return (strlen(cam_errbuf) != 0);
}