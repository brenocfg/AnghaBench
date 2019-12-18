#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  workspace; int /*<<< orphan*/  window_role; int /*<<< orphan*/  mark; int /*<<< orphan*/  instance; int /*<<< orphan*/  class; int /*<<< orphan*/  application; int /*<<< orphan*/  title; int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ Match ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regex_free (int /*<<< orphan*/ ) ; 

void match_free(Match *match) {
    FREE(match->error);
    regex_free(match->title);
    regex_free(match->application);
    regex_free(match->class);
    regex_free(match->instance);
    regex_free(match->mark);
    regex_free(match->window_role);
    regex_free(match->workspace);
}