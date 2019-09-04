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
 int /*<<< orphan*/  tv_box_xchacha20poly1305 () ; 
 int /*<<< orphan*/  tv_hchacha20 () ; 
 int /*<<< orphan*/  tv_secretbox_xchacha20poly1305 () ; 
 int /*<<< orphan*/  tv_stream_xchacha20 () ; 

int
main(void)
{
    tv_hchacha20();
    tv_stream_xchacha20();
    tv_secretbox_xchacha20poly1305();
    tv_box_xchacha20poly1305();

    return 0;
}