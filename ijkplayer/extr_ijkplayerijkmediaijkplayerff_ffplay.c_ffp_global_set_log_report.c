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
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffp_log_callback_brief ; 
 int /*<<< orphan*/  ffp_log_callback_report ; 

void ffp_global_set_log_report(int use_report)
{
    if (use_report) {
        av_log_set_callback(ffp_log_callback_report);
    } else {
        av_log_set_callback(ffp_log_callback_brief);
    }
}