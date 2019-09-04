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
 int normalize_path_copy_len (char*,char const*,int /*<<< orphan*/ *) ; 

int normalize_path_copy(char *dst, const char *src)
{
	return normalize_path_copy_len(dst, src, NULL);
}