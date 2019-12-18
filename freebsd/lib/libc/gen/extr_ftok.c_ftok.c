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
struct stat {int st_dev; int st_ino; } ;
typedef  int /*<<< orphan*/  key_t ;

/* Variables and functions */
 scalar_t__ stat (char const*,struct stat*) ; 

key_t
ftok(const char *path, int id)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return (key_t)-1;

	return ((key_t)((unsigned int)id << 24 | (st.st_dev & 0xff) << 16 |
	    (st.st_ino & 0xffff)));
}