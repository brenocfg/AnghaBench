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
typedef  int /*<<< orphan*/  tOptions ;
typedef  int /*<<< orphan*/  tOptionValue ;

/* Variables and functions */
 char const* skip_unkn (char const*) ; 

__attribute__((used)) static char const *
parse_set_mem(tOptions * opts, char const * txt, tOptionValue * typ)
{
    (void)opts;
    (void)typ;

    return skip_unkn(txt);
}