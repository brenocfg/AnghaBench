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
struct TYPE_2__ {long long version; long long stop_signal; long long cont_signal; } ;
typedef  TYPE_1__ i3bar_child ;

/* Variables and functions */
#define  KEY_CONT_SIGNAL 130 
#define  KEY_STOP_SIGNAL 129 
#define  KEY_VERSION 128 
 int current_key ; 

__attribute__((used)) static int header_integer(void *ctx, long long val) {
    i3bar_child *child = ctx;

    switch (current_key) {
        case KEY_VERSION:
            child->version = val;
            break;
        case KEY_STOP_SIGNAL:
            child->stop_signal = val;
            break;
        case KEY_CONT_SIGNAL:
            child->cont_signal = val;
            break;
        default:
            break;
    }

    return 1;
}