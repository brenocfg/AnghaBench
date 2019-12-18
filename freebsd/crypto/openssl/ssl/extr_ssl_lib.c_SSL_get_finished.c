#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* s3; } ;
struct TYPE_5__ {size_t finish_md_len; int /*<<< orphan*/  finish_md; } ;
struct TYPE_6__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 

size_t SSL_get_finished(const SSL *s, void *buf, size_t count)
{
    size_t ret = 0;

    if (s->s3 != NULL) {
        ret = s->s3->tmp.finish_md_len;
        if (count > ret)
            count = ret;
        memcpy(buf, s->s3->tmp.finish_md, count);
    }
    return ret;
}