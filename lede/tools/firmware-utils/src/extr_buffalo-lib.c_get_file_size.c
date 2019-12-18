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
struct stat {int st_size; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int stat (char*,struct stat*) ; 

ssize_t get_file_size(char *name)
{
	struct stat st;
	int err;

	err = stat(name, &st);
	if (err)
		return -1;

	return st.st_size;
}