#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* cb; } ;
typedef  TYPE_3__ quicly_sendbuf_vec_t ;
struct TYPE_9__ {size_t size; TYPE_3__* entries; } ;
struct TYPE_11__ {TYPE_2__ vecs; } ;
typedef  TYPE_4__ quicly_sendbuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* discard_vec ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void quicly_sendbuf_dispose(quicly_sendbuf_t *sb)
{
    size_t i;

    for (i = 0; i != sb->vecs.size; ++i) {
        quicly_sendbuf_vec_t *vec = sb->vecs.entries + i;
        if (vec->cb->discard_vec != NULL)
            vec->cb->discard_vec(vec);
    }
    free(sb->vecs.entries);
}