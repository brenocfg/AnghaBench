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
typedef  int /*<<< orphan*/  i3_shmlog_header ;
struct TYPE_2__ {scalar_t__ wrap_count; int offset_last_wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDOUT_FILENO ; 
 TYPE_1__* header ; 
 int logbuffer ; 
 int /*<<< orphan*/  swrite (int /*<<< orphan*/ ,int,int const) ; 
 int walk ; 
 scalar_t__ wrap_count ; 

__attribute__((used)) static int check_for_wrap(void) {
    if (wrap_count == header->wrap_count)
        return 0;

    /* The log wrapped. Print the remaining content and reset walk to the top
     * of the log. */
    wrap_count = header->wrap_count;
    const int len = (logbuffer + header->offset_last_wrap) - walk;
    swrite(STDOUT_FILENO, walk, len);
    walk = logbuffer + sizeof(i3_shmlog_header);
    return 1;
}