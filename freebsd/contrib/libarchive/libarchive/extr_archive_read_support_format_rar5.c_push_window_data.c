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
struct TYPE_2__ {int /*<<< orphan*/  window_buf; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct archive_read {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  push_data (struct archive_read*,struct rar5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_window_data(struct archive_read* a, struct rar5* rar,
    int64_t idx_begin, int64_t idx_end)
{
	push_data(a, rar, rar->cstate.window_buf, idx_begin, idx_end);
}