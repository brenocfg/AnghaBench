#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_mruby_http_sender_t {TYPE_1__* client; int /*<<< orphan*/ * remaining; int /*<<< orphan*/  sending; } ;
struct TYPE_6__ {scalar_t__ sender; } ;
typedef  TYPE_2__ h2o_mruby_generator_t ;
struct TYPE_5__ {TYPE_2__* shortcut; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_doublebuffer_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_sender_close_body (TYPE_2__*) ; 

__attribute__((used)) static void do_sender_dispose(h2o_mruby_generator_t *generator)
{
    struct st_h2o_mruby_http_sender_t *sender = (void *)generator->sender;

    h2o_doublebuffer_dispose(&sender->sending);

    /* note: no need to free reference from sender->client, since it is disposed at the same moment */
    if (sender->remaining != NULL)
        h2o_buffer_dispose(&sender->remaining);

    if (sender->client != NULL) {
        assert(sender->client->shortcut == generator);
        sender->client->shortcut = NULL;
    }

    h2o_mruby_sender_close_body(generator);
}