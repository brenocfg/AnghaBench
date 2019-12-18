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
 int /*<<< orphan*/  MB_TO_UC_FLAG ; 
 int /*<<< orphan*/  fb_flags ; 

void            
mb_to_uc_fb(const char* inbuf, size_t inbufsize,
    void (*write_replacement)(const unsigned int *buf, size_t buflen,
       void* callback_arg), void* callback_arg, void* data)
{

	fb_flags |= MB_TO_UC_FLAG;
}