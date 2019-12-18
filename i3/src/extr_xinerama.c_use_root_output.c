#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_6__ {int active; } ;
typedef  TYPE_1__ Output ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* create_root_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_ws_for_output (TYPE_1__*) ; 
 int /*<<< orphan*/  output_init_con (TYPE_1__*) ; 
 int /*<<< orphan*/  outputs ; 

__attribute__((used)) static void use_root_output(xcb_connection_t *conn) {
    Output *s = create_root_output(conn);
    s->active = true;
    TAILQ_INSERT_TAIL(&outputs, s, outputs);
    output_init_con(s);
    init_ws_for_output(s);
}