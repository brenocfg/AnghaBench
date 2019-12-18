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
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 void* fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibits ; 
 int /*<<< orphan*/  obits ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 void* tin ; 
 void* tout ; 
 int /*<<< orphan*/  xbits ; 

void
init_sys(void)
{
    tout = fileno(stdout);
    tin = fileno(stdin);
    FD_ZERO(&ibits);
    FD_ZERO(&obits);
    FD_ZERO(&xbits);

    errno = 0;
}