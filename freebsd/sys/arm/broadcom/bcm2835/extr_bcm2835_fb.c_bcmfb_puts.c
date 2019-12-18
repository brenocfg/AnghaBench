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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcmfb_putc (int /*<<< orphan*/ *,scalar_t__,int,int) ; 

__attribute__((used)) static int
bcmfb_puts(video_adapter_t *adp, vm_offset_t off, u_int16_t *s, int len)
{
	int i;

	for (i = 0; i < len; i++) 
		bcmfb_putc(adp, off + i, s[i] & 0xff, (s[i] & 0xff00) >> 8);

	return (0);
}