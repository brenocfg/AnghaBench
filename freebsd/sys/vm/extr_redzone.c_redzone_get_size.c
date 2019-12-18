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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  nsize ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ REDZONE_CHSIZE ; 
 int /*<<< orphan*/  bcopy (scalar_t__,int /*<<< orphan*/ *,int) ; 

u_long
redzone_get_size(caddr_t naddr)
{
	u_long nsize;

	bcopy(naddr - REDZONE_CHSIZE - sizeof(u_long), &nsize, sizeof(nsize));
	return (nsize);
}