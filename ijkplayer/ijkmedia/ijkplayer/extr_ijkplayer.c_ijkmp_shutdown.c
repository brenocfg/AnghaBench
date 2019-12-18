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
typedef  int /*<<< orphan*/  IjkMediaPlayer ;

/* Variables and functions */
 void ijkmp_shutdown_l (int /*<<< orphan*/ *) ; 

void ijkmp_shutdown(IjkMediaPlayer *mp)
{
    return ijkmp_shutdown_l(mp);
}