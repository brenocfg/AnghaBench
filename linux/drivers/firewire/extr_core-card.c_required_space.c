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
struct fw_descriptor {size_t length; scalar_t__ immediate; } ;

/* Variables and functions */

__attribute__((used)) static size_t required_space(struct fw_descriptor *desc)
{
	/* descriptor + entry into root dir + optional immediate entry */
	return desc->length + 1 + (desc->immediate > 0 ? 1 : 0);
}