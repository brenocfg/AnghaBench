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

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  h2o_error_printf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_strerror_r (int /*<<< orphan*/ ,char*,int) ; 

void h2o_perror(const char *msg)
{
    char buf[128];

    h2o_error_printf("%s: %s\n", msg, h2o_strerror_r(errno, buf, sizeof(buf)));
}