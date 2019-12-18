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
struct client {size_t olen; int /*<<< orphan*/  flags; int /*<<< orphan*/ * outmsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAITING_WRITE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * erealloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
output_data(struct client *c, const void *data, size_t len)
{
    if (c->olen + len < c->olen)
	abort();
    c->outmsg = erealloc(c->outmsg, c->olen + len);
    memcpy(&c->outmsg[c->olen], data, len);
    c->olen += len;
    c->flags |= WAITING_WRITE;
}