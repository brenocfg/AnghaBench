#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t len; int /*<<< orphan*/  buf; } ;
struct ident_filter {scalar_t__ state; TYPE_1__ left; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strbuf_remove (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void ident_drain(struct ident_filter *ident, char **output_p, size_t *osize_p)
{
	size_t to_drain = ident->left.len;

	if (*osize_p < to_drain)
		to_drain = *osize_p;
	if (to_drain) {
		memcpy(*output_p, ident->left.buf, to_drain);
		strbuf_remove(&ident->left, 0, to_drain);
		*output_p += to_drain;
		*osize_p -= to_drain;
	}
	if (!ident->left.len)
		ident->state = 0;
}