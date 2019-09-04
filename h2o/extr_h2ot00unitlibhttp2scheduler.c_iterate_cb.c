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
struct TYPE_2__ {char* name; int still_is_active; int bail_out; } ;
typedef  TYPE_1__ node_t ;
typedef  int /*<<< orphan*/  h2o_http2_scheduler_openref_t ;

/* Variables and functions */
 scalar_t__ max_cnt ; 
 char* output ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static int iterate_cb(h2o_http2_scheduler_openref_t *ref, int *still_is_active, void *_unused)
{
    node_t *node = (void *)ref;

    if (output[0] != '\0')
        strcat(output, ",");
    strcat(output, node->name);
    *still_is_active = node->still_is_active;

    if (--max_cnt == 0)
        return 1;
    return node->bail_out;
}