#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double percent; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,double,int /*<<< orphan*/ ) ; 
 TYPE_1__* json_node ; 
 int /*<<< orphan*/  last_key ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int json_double(void *ctx, double val) {
    LOG("double %f for key %s\n", val, last_key);
    if (strcasecmp(last_key, "percent") == 0) {
        json_node->percent = val;
    }
    return 1;
}