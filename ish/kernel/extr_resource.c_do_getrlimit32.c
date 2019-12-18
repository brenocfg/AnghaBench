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
struct rlimit_ {int /*<<< orphan*/  cur; int /*<<< orphan*/  max; } ;
struct rlimit32_ {int /*<<< orphan*/  cur; int /*<<< orphan*/  max; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int,...) ; 
 int /*<<< orphan*/  current ; 
 int rlimit_get (int /*<<< orphan*/ ,int,struct rlimit_*) ; 

__attribute__((used)) static int do_getrlimit32(int resource, struct rlimit32_ *rlimit32) {
    STRACE("getlimit(%d)", resource);
    struct rlimit_ rlimit;
    int err = rlimit_get(current, resource, &rlimit);
    if (err < 0)
        return err;
    STRACE(" {cur=%#x, max=%#x}", rlimit.cur, rlimit.max);

    rlimit32->max = rlimit.max;
    rlimit32->cur = rlimit.cur;
    return 0;
}