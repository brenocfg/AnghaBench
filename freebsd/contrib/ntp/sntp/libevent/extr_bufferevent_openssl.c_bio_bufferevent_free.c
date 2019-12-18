#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ptr; scalar_t__ flags; scalar_t__ init; scalar_t__ shutdown; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bio_bufferevent_free(BIO *b)
{
	if (!b)
		return 0;
	if (b->shutdown) {
		if (b->init && b->ptr)
			bufferevent_free(b->ptr);
		b->init = 0;
		b->flags = 0;
		b->ptr = NULL;
	}
	return 1;
}