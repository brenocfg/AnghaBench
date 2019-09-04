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
struct merge_options {scalar_t__ merge_detect_rename; scalar_t__ diff_detect_rename; } ;

/* Variables and functions */

__attribute__((used)) static inline int merge_detect_rename(struct merge_options *o)
{
	return o->merge_detect_rename >= 0 ? o->merge_detect_rename :
		o->diff_detect_rename >= 0 ? o->diff_detect_rename : 1;
}