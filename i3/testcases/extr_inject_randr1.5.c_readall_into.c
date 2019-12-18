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
 scalar_t__ read (int,void*,size_t const) ; 

__attribute__((used)) static size_t readall_into(void *buffer, const size_t len, int fd) {
    size_t read_bytes = 0;
    while (read_bytes < len) {
        ssize_t n = read(fd, buffer + read_bytes, len - read_bytes);
        if (n <= 0) {
            return n;
        }
        read_bytes += (size_t)n;
    }
    return read_bytes;
}