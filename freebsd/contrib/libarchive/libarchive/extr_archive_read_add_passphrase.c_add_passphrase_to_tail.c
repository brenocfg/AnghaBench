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
struct archive_read_passphrase {struct archive_read_passphrase* next; } ;
struct TYPE_2__ {struct archive_read_passphrase** last; } ;
struct archive_read {TYPE_1__ passphrases; } ;

/* Variables and functions */

__attribute__((used)) static void
add_passphrase_to_tail(struct archive_read *a,
    struct archive_read_passphrase *p)
{
	*a->passphrases.last = p;
	a->passphrases.last = &p->next;
	p->next = NULL;
}