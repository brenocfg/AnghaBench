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
 int /*<<< orphan*/  VIO_PROBE_ONLY ; 
 int /*<<< orphan*/  vid_configure (int /*<<< orphan*/ ) ; 
 scalar_t__ vid_find_adapter (char*,int) ; 

__attribute__((used)) static int
scvidprobe(int unit, int flags, int cons)
{
    /*
     * Access the video adapter driver through the back door!
     * Video adapter drivers need to be configured before syscons.
     * However, when syscons is being probed as the low-level console,
     * they have not been initialized yet.  We force them to initialize
     * themselves here. XXX
     */
    vid_configure(cons ? VIO_PROBE_ONLY : 0);

    return (vid_find_adapter("*", unit) >= 0);
}