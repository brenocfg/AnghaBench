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
 scalar_t__ INT_MAX ; 
 int cat_blob_fd ; 
 int /*<<< orphan*/  die (char*,scalar_t__) ; 
 unsigned long ulong_arg (char*,char const*) ; 

__attribute__((used)) static void option_cat_blob_fd(const char *fd)
{
	unsigned long n = ulong_arg("--cat-blob-fd", fd);
	if (n > (unsigned long) INT_MAX)
		die("--cat-blob-fd cannot exceed %d", INT_MAX);
	cat_blob_fd = (int) n;
}