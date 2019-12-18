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
 int /*<<< orphan*/  free (char*) ; 
 char* locate_in_PATH (char const*) ; 

__attribute__((used)) static int exists_in_PATH(const char *file)
{
	char *r = locate_in_PATH(file);
	free(r);
	return r != NULL;
}