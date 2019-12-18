#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; scalar_t__ ptr; } ;
struct TYPE_8__ {TYPE_1__* buf; TYPE_1__* readp; } ;
struct TYPE_7__ {int length; char* data; } ;
typedef  TYPE_1__ BUF_MEM ;
typedef  TYPE_2__ BIO_BUF_MEM ;
typedef  TYPE_3__ BIO ;

/* Variables and functions */
 int BIO_FLAGS_MEM_RDONLY ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_3__*) ; 
 int mem_read (TYPE_3__*,char*,int) ; 

__attribute__((used)) static int mem_gets(BIO *bp, char *buf, int size)
{
    int i, j;
    int ret = -1;
    char *p;
    BIO_BUF_MEM *bbm = (BIO_BUF_MEM *)bp->ptr;
    BUF_MEM *bm = bbm->readp;

    if (bp->flags & BIO_FLAGS_MEM_RDONLY)
        bm = bbm->buf;
    BIO_clear_retry_flags(bp);
    j = bm->length;
    if ((size - 1) < j)
        j = size - 1;
    if (j <= 0) {
        *buf = '\0';
        return 0;
    }
    p = bm->data;
    for (i = 0; i < j; i++) {
        if (p[i] == '\n') {
            i++;
            break;
        }
    }

    /*
     * i is now the max num of bytes to copy, either j or up to
     * and including the first newline
     */

    i = mem_read(bp, buf, i);
    if (i > 0)
        buf[i] = '\0';
    ret = i;
    return ret;
}