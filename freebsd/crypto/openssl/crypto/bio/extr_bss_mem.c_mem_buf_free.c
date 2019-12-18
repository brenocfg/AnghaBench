#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/ * ptr; scalar_t__ init; scalar_t__ shutdown; } ;
struct TYPE_7__ {TYPE_1__* buf; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_2__ BIO_BUF_MEM ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BUF_MEM_free (TYPE_1__*) ; 

__attribute__((used)) static int mem_buf_free(BIO *a)
{
    if (a == NULL)
        return 0;

    if (a->shutdown && a->init && a->ptr != NULL) {
        BIO_BUF_MEM *bb = (BIO_BUF_MEM *)a->ptr;
        BUF_MEM *b = bb->buf;

        if (a->flags & BIO_FLAGS_MEM_RDONLY)
            b->data = NULL;
        BUF_MEM_free(b);
    }
    return 1;
}