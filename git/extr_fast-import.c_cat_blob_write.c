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
 int /*<<< orphan*/  cat_blob_fd ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ write_in_full (int /*<<< orphan*/ ,char const*,unsigned long) ; 

__attribute__((used)) static void cat_blob_write(const char *buf, unsigned long size)
{
	if (write_in_full(cat_blob_fd, buf, size) < 0)
		die_errno("Write to frontend failed");
}