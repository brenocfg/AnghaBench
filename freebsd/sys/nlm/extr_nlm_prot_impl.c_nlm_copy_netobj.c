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
struct netobj {int /*<<< orphan*/  n_len; int /*<<< orphan*/  n_bytes; } ;
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_make_netobj (struct netobj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct malloc_type*) ; 

void
nlm_copy_netobj(struct netobj *dst, struct netobj *src,
    struct malloc_type *type)
{

	nlm_make_netobj(dst, src->n_bytes, src->n_len, type);
}