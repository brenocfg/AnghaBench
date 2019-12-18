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
struct TYPE_2__ {char* input; char* errorposition; char* error; int /*<<< orphan*/  success; } ;

/* Variables and functions */
 int exit_code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__ last_reply ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int reply_end_map_cb(void *params) {
    if (!last_reply.success) {
        if (last_reply.input) {
            fprintf(stderr, "ERROR: Your command: %s\n", last_reply.input);
            fprintf(stderr, "ERROR:               %s\n", last_reply.errorposition);
        }
        fprintf(stderr, "ERROR: %s\n", last_reply.error);
        exit_code = 2;
    }
    return 1;
}