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
struct rlimit_ {int /*<<< orphan*/  cur; } ;
typedef  int /*<<< orphan*/  rlim_t_ ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  die (char*,int) ; 
 scalar_t__ rlimit_get (int /*<<< orphan*/ ,int,struct rlimit_*) ; 

rlim_t_ rlimit(int resource) {
    struct rlimit_ limit;
    if (rlimit_get(current, resource, &limit) != 0)
        die("invalid resource %d", resource);
    return limit.cur;
}