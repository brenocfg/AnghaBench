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
typedef  size_t dword_t ;
typedef  size_t addr_t ;

/* Variables and functions */
 size_t strings_size (char const*) ; 
 scalar_t__ user_write (size_t,char const*,size_t) ; 

__attribute__((used)) static inline dword_t copy_strings(addr_t sp, const char *strings) {
    size_t size = strings_size(strings);
    sp -= size;
    if (user_write(sp, strings, size))
        return 0;
    return sp;
}