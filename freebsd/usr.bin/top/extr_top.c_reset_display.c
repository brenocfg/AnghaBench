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
 int /*<<< orphan*/  d_arc ; 
 int /*<<< orphan*/  d_carc ; 
 int /*<<< orphan*/  d_cpustates ; 
 int /*<<< orphan*/  d_header ; 
 int /*<<< orphan*/  d_loadave ; 
 int /*<<< orphan*/  d_memory ; 
 int /*<<< orphan*/  d_message ; 
 int /*<<< orphan*/  d_process ; 
 int /*<<< orphan*/  d_procstates ; 
 int /*<<< orphan*/  d_swap ; 
 int /*<<< orphan*/  i_arc ; 
 int /*<<< orphan*/  i_carc ; 
 int /*<<< orphan*/  i_cpustates ; 
 int /*<<< orphan*/  i_header ; 
 int /*<<< orphan*/  i_loadave ; 
 int /*<<< orphan*/  i_memory ; 
 int /*<<< orphan*/  i_message ; 
 int /*<<< orphan*/  i_process ; 
 int /*<<< orphan*/  i_procstates ; 
 int /*<<< orphan*/  i_swap ; 

__attribute__((used)) static void
reset_display(void)
{
    d_loadave    = i_loadave;
    d_procstates = i_procstates;
    d_cpustates  = i_cpustates;
    d_memory     = i_memory;
    d_arc        = i_arc;
    d_carc       = i_carc;
    d_swap       = i_swap;
    d_message	 = i_message;
    d_header	 = i_header;
    d_process	 = i_process;
}