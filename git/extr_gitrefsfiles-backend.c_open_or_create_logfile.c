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
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int open (char const*,int,int) ; 

__attribute__((used)) static int open_or_create_logfile(const char *path, void *cb)
{
	int *fd = cb;

	*fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0666);
	return (*fd < 0) ? -1 : 0;
}