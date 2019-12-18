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
struct bufferevent_openssl {scalar_t__ n_errors; scalar_t__* errors; } ;
typedef  scalar_t__ ev_uint32_t ;

/* Variables and functions */
 scalar_t__ NUM_ERRORS ; 

__attribute__((used)) static inline void
put_error(struct bufferevent_openssl *bev_ssl, unsigned long err)
{
	if (bev_ssl->n_errors == NUM_ERRORS)
		return;
	/* The error type according to openssl is "unsigned long", but
	   openssl never uses more than 32 bits of it.  It _can't_ use more
	   than 32 bits of it, since it needs to report errors on systems
	   where long is only 32 bits.
	 */
	bev_ssl->errors[bev_ssl->n_errors++] = (ev_uint32_t) err;
}