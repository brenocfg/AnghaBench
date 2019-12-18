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
typedef  int /*<<< orphan*/  uchar ;

/* Variables and functions */
 int dowild (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 

int wildmatch(const char *pattern, const char *text, unsigned int flags)
{
	return dowild((const uchar*)pattern, (const uchar*)text, flags);
}