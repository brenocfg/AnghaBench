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
 int /*<<< orphan*/  ui_file_write (void*,char const*,long) ; 

__attribute__((used)) static void
do_write (void *data, const char *buffer, long length_buffer)
{
  ui_file_write (data, buffer, length_buffer);
}