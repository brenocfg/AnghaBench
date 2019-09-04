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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  clamp_max (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  copy_le32 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_le32_clamp(unsigned char *dest, uint64_t n, int *clamped)
{
	copy_le32(dest, clamp_max(n, 0xffffffff, clamped));
}