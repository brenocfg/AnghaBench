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
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int open (char const*,int,unsigned int) ; 

__attribute__((used)) static int create_file(const char *path, unsigned int mode)
{
	mode = (mode & 0100) ? 0777 : 0666;
	return open(path, O_WRONLY | O_CREAT | O_EXCL, mode);
}