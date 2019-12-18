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
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  trayclient ;

/* Variables and functions */
 int /*<<< orphan*/ * trayclient_and_output_from_window (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static trayclient *trayclient_from_window(xcb_window_t win) {
    return trayclient_and_output_from_window(win, NULL);
}