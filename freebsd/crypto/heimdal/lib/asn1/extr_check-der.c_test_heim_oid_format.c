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
struct TYPE_3__ {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ heim_oid ;

/* Variables and functions */
 int /*<<< orphan*/  sha1_oid_tree ; 
 scalar_t__ test_heim_oid_format_same (char*,TYPE_1__*) ; 

__attribute__((used)) static int
test_heim_oid_format(void)
{
    heim_oid sha1 = { 6, sha1_oid_tree };
    int ret = 0;

    ret += test_heim_oid_format_same("1 3 14 3 2 26", &sha1);

    return ret;
}