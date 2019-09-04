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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 size_t strlen (char const*) ; 
 scalar_t__ write (int,char const*,size_t) ; 

__attribute__((used)) static inline void
write_to_stderr(const char *text) {
    size_t sz = strlen(text);
    size_t written = 0;
    while(written < sz) {
        ssize_t amt = write(2, text + written, sz - written);
        if (amt == 0) break;
        if (amt < 0) {
            if (errno == EAGAIN || errno == EINTR) continue;
            break;
        }
        written += amt;
    }
}