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
 unsigned int ACCESS_EACCES_OK ; 
 int EACCES ; 
 scalar_t__ is_missing_file_error (int) ; 

__attribute__((used)) static int access_error_is_ok(int err, unsigned flag)
{
	return (is_missing_file_error(err) ||
		((flag & ACCESS_EACCES_OK) && err == EACCES));
}