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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 scalar_t__ user_read (scalar_t__,char*,int) ; 

int user_read_string(addr_t addr, char *buf, size_t max) {
    if (addr == 0)
        return 1;
    size_t i = 0;
    while (i < max) {
        if (user_read(addr + i, &buf[i], sizeof(buf[i])))
            return 1;
        if (buf[i] == '\0')
            break;
        i++;
    }
    return 0;
}