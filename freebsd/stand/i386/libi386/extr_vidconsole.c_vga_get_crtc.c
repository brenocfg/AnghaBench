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
 int /*<<< orphan*/  VGA_CRTC_ADDRESS ; 
 int /*<<< orphan*/  VGA_CRTC_DATA ; 
 int vga_get_indexed (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
vga_get_crtc(int reg, int i)
{
	return (vga_get_indexed(reg, VGA_CRTC_ADDRESS, VGA_CRTC_DATA, i));
}