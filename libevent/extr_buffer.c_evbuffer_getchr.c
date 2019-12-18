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
struct TYPE_2__ {size_t pos_in_chain; struct evbuffer_chain* chain; } ;
struct evbuffer_ptr {TYPE_1__ internal_; } ;
struct evbuffer_chain {size_t misalign; scalar_t__* buffer; } ;

/* Variables and functions */

__attribute__((used)) static inline int
evbuffer_getchr(struct evbuffer_ptr *it)
{
	struct evbuffer_chain *chain = it->internal_.chain;
	size_t off = it->internal_.pos_in_chain;

	if (chain == NULL)
		return -1;

	return (unsigned char)chain->buffer[chain->misalign + off];
}