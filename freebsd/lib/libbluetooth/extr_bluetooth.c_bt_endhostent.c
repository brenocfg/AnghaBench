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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ host_stayopen ; 
 int /*<<< orphan*/ * hostf ; 

void
bt_endhostent(void)
{
	if (hostf != NULL && host_stayopen == 0) {
		(void) fclose(hostf);
		hostf = NULL;
	}
}