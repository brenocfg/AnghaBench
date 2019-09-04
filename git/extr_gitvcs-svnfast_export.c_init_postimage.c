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
 int buffer_tmpfile_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  postimage ; 

__attribute__((used)) static int init_postimage(void)
{
	static int postimage_initialized;
	if (postimage_initialized)
		return 0;
	postimage_initialized = 1;
	return buffer_tmpfile_init(&postimage);
}