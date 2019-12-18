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
typedef  scalar_t__ utf8_int32_t ;

/* Variables and functions */
 scalar_t__ utf8uprcodepoint (scalar_t__) ; 

int utf8islower(utf8_int32_t chr) { return chr != utf8uprcodepoint(chr); }