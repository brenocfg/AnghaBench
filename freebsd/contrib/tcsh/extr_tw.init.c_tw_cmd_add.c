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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  Strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int Strlen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tw_cmd ; 
 int /*<<< orphan*/  tw_str_add (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
tw_cmd_add(const Char *name)
{
    size_t len;

    len = Strlen(name) + 2;
    (void) Strcpy(tw_str_add(&tw_cmd, len), name);
}