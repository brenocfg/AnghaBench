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
 unsigned int S_IFGITLINK ; 
 unsigned int S_IFLNK ; 
 unsigned int S_IFREG ; 
 scalar_t__ S_ISDIR (unsigned int) ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 scalar_t__ S_ISLNK (unsigned int) ; 
 unsigned int ce_permissions (unsigned int) ; 

__attribute__((used)) static inline unsigned int create_ce_mode(unsigned int mode)
{
	if (S_ISLNK(mode))
		return S_IFLNK;
	if (S_ISDIR(mode) || S_ISGITLINK(mode))
		return S_IFGITLINK;
	return S_IFREG | ce_permissions(mode);
}