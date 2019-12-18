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
struct TYPE_3__ {int num; scalar_t__ flags; int /*<<< orphan*/ * ptr; scalar_t__ init; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */

__attribute__((used)) static int
bio_bufferevent_new(BIO *b)
{
	b->init = 0;
	b->num = -1;
	b->ptr = NULL; /* We'll be putting the bufferevent in this field.*/
	b->flags = 0;
	return 1;
}