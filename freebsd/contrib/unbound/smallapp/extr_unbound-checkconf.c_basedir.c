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
 int /*<<< orphan*/  fatal_exit (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char*
basedir(char* fname)
{
	char* rev;
	if(!fname) fatal_exit("out of memory");
	rev = strrchr(fname, '/');
	if(!rev) return NULL;
	if(fname == rev) return NULL;
	rev[0] = 0;
	return fname;
}