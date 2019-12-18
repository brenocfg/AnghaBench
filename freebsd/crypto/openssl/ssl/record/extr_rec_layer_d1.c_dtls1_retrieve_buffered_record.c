#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ record_pqueue ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ pitem ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtls1_copy_record (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pitem_free (TYPE_2__*) ; 
 TYPE_2__* pqueue_pop (int /*<<< orphan*/ ) ; 

int dtls1_retrieve_buffered_record(SSL *s, record_pqueue *queue)
{
    pitem *item;

    item = pqueue_pop(queue->q);
    if (item) {
        dtls1_copy_record(s, item);

        OPENSSL_free(item->data);
        pitem_free(item);

        return 1;
    }

    return 0;
}