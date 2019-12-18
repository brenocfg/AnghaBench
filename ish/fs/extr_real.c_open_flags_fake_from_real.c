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
 int O_APPEND_ ; 
 int O_CREAT ; 
 int O_CREAT_ ; 
 int O_NONBLOCK ; 
 int O_NONBLOCK_ ; 
 int O_RDONLY ; 
 int O_RDONLY_ ; 
 int O_RDWR ; 
 int O_RDWR_ ; 
 int O_TRUNC ; 
 int O_TRUNC_ ; 
 int O_WRONLY ; 
 int O_WRONLY_ ; 

__attribute__((used)) static int open_flags_fake_from_real(int flags) {
    int fake_flags = 0;
    if (flags & O_RDONLY) fake_flags |= O_RDONLY_;
    if (flags & O_WRONLY) fake_flags |= O_WRONLY_;
    if (flags & O_RDWR) fake_flags |= O_RDWR_;
    if (flags & O_CREAT) fake_flags |= O_CREAT_;
    if (flags & O_TRUNC) fake_flags |= O_TRUNC_;
    if (flags & O_APPEND) fake_flags |= O_APPEND_;
    if (flags & O_NONBLOCK) fake_flags |= O_NONBLOCK_;
    return fake_flags;
}