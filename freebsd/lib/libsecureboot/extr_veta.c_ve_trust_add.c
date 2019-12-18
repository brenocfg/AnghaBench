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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int trust_dir_add (char const*) ; 
 int trust_file_add (char const*) ; 

int
ve_trust_add(const char *trust)
{
	struct stat st;

	if (stat(trust, &st) < 0)
		return (-1);
	if (S_ISDIR(st.st_mode))
		return (trust_dir_add(trust));
	return (trust_file_add(trust));
}