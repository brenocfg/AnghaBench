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
struct TYPE_3__ {scalar_t__ off; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int buffer_is(ptls_buffer_t *buf, const char *s)
{
    return buf->off == strlen(s) && memcmp(buf->base, s, buf->off) == 0;
}