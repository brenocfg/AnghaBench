#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct diff_filepair {TYPE_1__* two; } ;
struct TYPE_2__ {char const* path; } ;

/* Variables and functions */

__attribute__((used)) static const char *pair_pathtwo(void *obj)
{
	struct diff_filepair *pair = (struct diff_filepair *)obj;

	return pair->two->path;
}