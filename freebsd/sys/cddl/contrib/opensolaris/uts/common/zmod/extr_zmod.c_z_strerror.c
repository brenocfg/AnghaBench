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
 int Z_NEED_DICT ; 
 int Z_VERSION_ERROR ; 
 char const* zError (int) ; 

const char *
z_strerror(int err)
{
	int i = Z_NEED_DICT - err;

	if (i < 0 || i > Z_NEED_DICT - Z_VERSION_ERROR)
		return ("unknown error");

	return (zError(err));
}