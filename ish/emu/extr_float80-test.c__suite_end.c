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
 int /*<<< orphan*/  printf (char*,char const*,int,double,double) ; 
 int suite_passed ; 
 double suite_total ; 

void _suite_end(const char *suite) {
    printf("%s: %d/%d passed (%.0f%%)\n", suite, suite_passed, suite_total, (double) suite_passed / suite_total * 100);
}