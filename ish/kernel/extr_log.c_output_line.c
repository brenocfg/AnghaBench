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
 int /*<<< orphan*/  log_buf_append (char const*) ; 
 int /*<<< orphan*/  log_line (char const*) ; 

__attribute__((used)) static void output_line(const char *line) {
    // send it to stdout or wherever
    log_line(line);
    // add it to the circular buffer
    log_buf_append(line);
    log_buf_append("\n");
}