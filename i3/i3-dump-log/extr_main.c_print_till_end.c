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
struct TYPE_2__ {int offset_next_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  check_for_wrap () ; 
 TYPE_1__* header ; 
 int logbuffer ; 
 int /*<<< orphan*/  swrite (int /*<<< orphan*/ ,int,int const) ; 
 int walk ; 

__attribute__((used)) static void print_till_end(void) {
    check_for_wrap();
    const int len = (logbuffer + header->offset_next_write) - walk;
    swrite(STDOUT_FILENO, walk, len);
    walk += len;
}