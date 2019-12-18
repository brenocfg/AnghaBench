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
struct TYPE_2__ {int success; } ;

/* Variables and functions */
 int /*<<< orphan*/  last_key ; 
 TYPE_1__ last_reply ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int reply_boolean_cb(void *params, int val) {
    if (strcmp(last_key, "success") == 0)
        last_reply.success = val;
    return 1;
}