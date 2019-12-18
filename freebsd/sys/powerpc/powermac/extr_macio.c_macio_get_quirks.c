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
struct macio_quirk_entry {int mq_quirks; int /*<<< orphan*/ * mq_name; } ;

/* Variables and functions */
 struct macio_quirk_entry* macio_quirks ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
macio_get_quirks(const char *name)
{
        struct	macio_quirk_entry *mqe;

        for (mqe = macio_quirks; mqe->mq_name != NULL; mqe++)
                if (strcmp(name, mqe->mq_name) == 0)
                        return (mqe->mq_quirks);
        return (0);
}