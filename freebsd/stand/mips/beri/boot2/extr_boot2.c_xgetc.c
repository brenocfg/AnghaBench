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
 int IO_KEYBOARD ; 
 int IO_SERIAL ; 
 scalar_t__ OPT_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBX_NOINTR ; 
 int beri_getc () ; 
 int ioctrl ; 
 scalar_t__ keyhit (int /*<<< orphan*/ ) ; 
 int sio_getc () ; 
 scalar_t__ sio_ischar () ; 

__attribute__((used)) static int
xgetc(int fn)
{
    if (OPT_CHECK(RBX_NOINTR))
	return 0;
    for (;;) {
	if (ioctrl & IO_KEYBOARD && keyhit(0))
	    return fn ? 1 : beri_getc();
#if 0
	if (ioctrl & IO_SERIAL && sio_ischar())
	    return fn ? 1 : sio_getc();
#endif
	if (fn)
	    return 0;
    }
}