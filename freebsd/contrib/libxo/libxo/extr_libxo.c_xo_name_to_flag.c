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
 int /*<<< orphan*/  xo_name_lookup (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  xo_xof_names ; 

__attribute__((used)) static unsigned
xo_name_to_flag (const char *name)
{
    return (unsigned) xo_name_lookup(xo_xof_names, name, -1);
}