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
 int /*<<< orphan*/ * extbuf ; 
 size_t extbufsize ; 
 size_t extloc ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
xtrattr(char *buf, size_t size)
{

	if (extloc + size > extbufsize)
		panic("overrun attribute buffer\n");
	memmove(&extbuf[extloc], buf, size);
	extloc += size;
}