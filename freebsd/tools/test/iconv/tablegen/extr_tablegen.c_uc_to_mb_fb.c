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
 int /*<<< orphan*/  UC_TO_MB_FLAG ; 
 int /*<<< orphan*/  fb_flags ; 

void
uc_to_mb_fb(unsigned int code,
    void (*write_replacement)(const char *buf, size_t buflen,
       void* callback_arg), void* callback_arg, void* data)
{

	fb_flags |= UC_TO_MB_FLAG;
}