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
struct lun {int /*<<< orphan*/  l_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  checked_strdup (char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
lun_set_backend(struct lun *lun, const char *value)
{
	free(lun->l_backend);
	lun->l_backend = checked_strdup(value);
}