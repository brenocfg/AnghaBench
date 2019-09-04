#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_save_ticket_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ saved_ticket ; 

__attribute__((used)) static int on_save_ticket(ptls_save_ticket_t *self, ptls_t *tls, ptls_iovec_t src)
{
    saved_ticket.base = malloc(src.len);
    memcpy(saved_ticket.base, src.base, src.len);
    saved_ticket.len = src.len;
    return 0;
}