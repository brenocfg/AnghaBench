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
struct am_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  am_path (struct am_state const*,char const*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void write_state_text(const struct am_state *state,
			     const char *name, const char *string)
{
	write_file(am_path(state, name), "%s", string);
}