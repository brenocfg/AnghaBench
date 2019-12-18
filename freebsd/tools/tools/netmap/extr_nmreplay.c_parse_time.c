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
typedef  int /*<<< orphan*/  uint64_t ;
struct _sm {char* member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  U_PARSE_ERR ; 
 int /*<<< orphan*/  parse_gen (char const*,struct _sm*,int*) ; 

__attribute__((used)) static uint64_t
parse_time(const char *arg)
{
    struct _sm a[] = {
	{"", 1000000000 /* seconds */},
	{"n", 1 /* nanoseconds */}, {"u", 1000 /* microseconds */},
	{"m", 1000000 /* milliseconds */}, {"s", 1000000000 /* seconds */},
	{NULL, 0 /* seconds */}
    };
    int err;
    uint64_t ret = (uint64_t)parse_gen(arg, a, &err);
    return err ? U_PARSE_ERR : ret;
}