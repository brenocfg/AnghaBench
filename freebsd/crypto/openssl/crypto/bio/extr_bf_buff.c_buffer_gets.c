#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  next_bio; scalar_t__ ptr; } ;
struct TYPE_6__ {int ibuf_len; char* ibuf; size_t ibuf_off; int /*<<< orphan*/  ibuf_size; } ;
typedef  TYPE_1__ BIO_F_BUFFER_CTX ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_2__*) ; 
 int BIO_read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int buffer_gets(BIO *b, char *buf, int size)
{
    BIO_F_BUFFER_CTX *ctx;
    int num = 0, i, flag;
    char *p;

    ctx = (BIO_F_BUFFER_CTX *)b->ptr;
    size--;                     /* reserve space for a '\0' */
    BIO_clear_retry_flags(b);

    for (;;) {
        if (ctx->ibuf_len > 0) {
            p = &(ctx->ibuf[ctx->ibuf_off]);
            flag = 0;
            for (i = 0; (i < ctx->ibuf_len) && (i < size); i++) {
                *(buf++) = p[i];
                if (p[i] == '\n') {
                    flag = 1;
                    i++;
                    break;
                }
            }
            num += i;
            size -= i;
            ctx->ibuf_len -= i;
            ctx->ibuf_off += i;
            if (flag || size == 0) {
                *buf = '\0';
                return num;
            }
        } else {                /* read another chunk */

            i = BIO_read(b->next_bio, ctx->ibuf, ctx->ibuf_size);
            if (i <= 0) {
                BIO_copy_next_retry(b);
                *buf = '\0';
                if (i < 0)
                    return ((num > 0) ? num : i);
                if (i == 0)
                    return num;
            }
            ctx->ibuf_len = i;
            ctx->ibuf_off = 0;
        }
    }
}