#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* str; } ;
struct TYPE_4__ {char const* identifier; int /*<<< orphan*/  type; TYPE_1__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_STR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* stack ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void push_string(const char *identifier, char *str) {
    for (int c = 0; c < 10; c++) {
        if (stack[c].identifier != NULL)
            continue;
        /* Found a free slot, let’s store it here. */
        stack[c].identifier = identifier;
        stack[c].val.str = str;
        stack[c].type = STACK_STR;
        return;
    }

    /* When we arrive here, the stack is full. This should not happen and
     * means there’s either a bug in this parser or the specification
     * contains a command with more than 10 identified tokens. */
    fprintf(stderr, "BUG: commands_parser stack full. This means either a bug "
                    "in the code, or a new command which contains more than "
                    "10 identified tokens.\n");
    exit(1);
}