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
struct TYPE_2__ {int /*<<< orphan*/ * key; } ;
struct expected {TYPE_1__ l; } ;

/* Variables and functions */
 int /*<<< orphan*/  sshkey_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cleanup_expected(struct expected *expected, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		sshkey_free(expected[i].l.key);
		expected[i].l.key = NULL;
	}
}