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
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int cmpstrptr(const void *_x, const void *_y)
{
    const char *x = *(const char **)_x;
    const char *y = *(const char **)_y;
    return strcmp(x, y);
}