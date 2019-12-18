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
struct clnt_str {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */

__attribute__((used)) static void
init_clnt_str(struct clnt_str *cs)
{
	cs->data = NULL;
	cs->len = 0;
}