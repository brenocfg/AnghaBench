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

__attribute__((used)) static unsigned long
amr_ioctl_buffer_length(unsigned long len)
{

    if (len <= 4 * 1024)
	return (4 * 1024);
    if (len <= 8 * 1024)
	return (8 * 1024);
    if (len <= 32 * 1024)
	return (32 * 1024);
    if (len <= 64 * 1024)
	return (64 * 1024);
    return (len);
}