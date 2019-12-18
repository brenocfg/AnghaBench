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
 short ABSENT_NUMERIC ; 
 short CANCELLED_NUMERIC ; 
 int /*<<< orphan*/  LITTLE_ENDIAN (unsigned char*,short) ; 
 int /*<<< orphan*/  TRACE_OUT (char*) ; 

__attribute__((used)) static void
convert_shorts(unsigned char *buf, short *Numbers, size_t count)
{
    size_t i;
    for (i = 0; i < count; i++) {
	if (Numbers[i] == ABSENT_NUMERIC) {	/* HI/LO won't work */
	    buf[2 * i] = buf[2 * i + 1] = 0377;
	} else if (Numbers[i] == CANCELLED_NUMERIC) {	/* HI/LO won't work */
	    buf[2 * i] = 0376;
	    buf[2 * i + 1] = 0377;
	} else {
	    LITTLE_ENDIAN(buf + 2 * i, Numbers[i]);
	    TRACE_OUT(("put Numbers[%u]=%d", (unsigned) i, Numbers[i]));
	}
    }
}