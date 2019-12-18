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
 int EAGAIN ; 
 int EEXIST ; 
 int EINPROGRESS ; 
 int ENOENT ; 
 int ENOTCONN ; 
 int EXDEV ; 
 void syscall_ret_l1d_flush () ; 

__attribute__((used)) static void __inline
amd64_syscall_ret_flush_l1d_inline(int error)
{
	void (*p)(void);

	if (error != 0 && error != EEXIST && error != EAGAIN &&
	    error != EXDEV && error != ENOENT && error != ENOTCONN &&
	    error != EINPROGRESS) {
		p = syscall_ret_l1d_flush;
		if (p != NULL)
			p();
	}
}