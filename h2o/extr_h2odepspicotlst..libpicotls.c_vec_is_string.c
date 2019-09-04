#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t len; scalar_t__ base; } ;
typedef  TYPE_1__ ptls_iovec_t ;

/* Variables and functions */
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int vec_is_string(ptls_iovec_t x, const char *y)
{
    return strncmp((const char *)x.base, y, x.len) == 0 && y[x.len] == '\0';
}