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
struct evbuffer_cb_info {size_t orig_size; size_t n_added; size_t n_deleted; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
log_change_callback(struct evbuffer *buffer,
    const struct evbuffer_cb_info *cbinfo,
    void *arg)
{

	size_t old_len = cbinfo->orig_size;
	size_t new_len = old_len + cbinfo->n_added - cbinfo->n_deleted;
	struct evbuffer *out = arg;
	evbuffer_add_printf(out, "%lu->%lu; ", (unsigned long)old_len,
			    (unsigned long)new_len);
}