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
#define  LINUX_POSIX_FADV_DONTNEED 133 
#define  LINUX_POSIX_FADV_NOREUSE 132 
#define  LINUX_POSIX_FADV_NORMAL 131 
#define  LINUX_POSIX_FADV_RANDOM 130 
#define  LINUX_POSIX_FADV_SEQUENTIAL 129 
#define  LINUX_POSIX_FADV_WILLNEED 128 
 int POSIX_FADV_DONTNEED ; 
 int POSIX_FADV_NOREUSE ; 
 int POSIX_FADV_NORMAL ; 
 int POSIX_FADV_RANDOM ; 
 int POSIX_FADV_SEQUENTIAL ; 
 int POSIX_FADV_WILLNEED ; 

__attribute__((used)) static int
convert_fadvice(int advice)
{
	switch (advice) {
	case LINUX_POSIX_FADV_NORMAL:
		return (POSIX_FADV_NORMAL);
	case LINUX_POSIX_FADV_RANDOM:
		return (POSIX_FADV_RANDOM);
	case LINUX_POSIX_FADV_SEQUENTIAL:
		return (POSIX_FADV_SEQUENTIAL);
	case LINUX_POSIX_FADV_WILLNEED:
		return (POSIX_FADV_WILLNEED);
	case LINUX_POSIX_FADV_DONTNEED:
		return (POSIX_FADV_DONTNEED);
	case LINUX_POSIX_FADV_NOREUSE:
		return (POSIX_FADV_NOREUSE);
	default:
		return (-1);
	}
}