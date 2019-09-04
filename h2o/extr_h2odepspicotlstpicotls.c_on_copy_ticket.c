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
typedef  int /*<<< orphan*/  ptls_t ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
typedef  int /*<<< orphan*/  ptls_encrypt_ticket_t ;
struct TYPE_7__ {scalar_t__ off; scalar_t__ base; } ;
typedef  TYPE_2__ ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int ptls_buffer_reserve (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int on_copy_ticket(ptls_encrypt_ticket_t *self, ptls_t *tls, int is_encrypt, ptls_buffer_t *dst, ptls_iovec_t src)
{
    int ret;

    if ((ret = ptls_buffer_reserve(dst, src.len)) != 0)
        return ret;
    memcpy(dst->base + dst->off, src.base, src.len);
    dst->off += src.len;

    return 0;
}