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
struct wlc_call {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* wlc_calls ; 
 int wlc_calls_size ; 

__attribute__((used)) static struct wlc_call *find_cmd(char *name)
{
	int found = 0, i = 0;

	while (!found && (i < wlc_calls_size)) {
		if (strcmp(name, wlc_calls[i].name) == 0)
			found = 1;
		else
			i++;
	}

	return (struct wlc_call *) (found ? &wlc_calls[i] : NULL);
}