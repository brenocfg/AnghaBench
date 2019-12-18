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

/* Variables and functions */
 size_t INTERPOS_distribute_static_tls ; 
 scalar_t__* __libc_interposing ; 
 void stub1 (size_t,void*,size_t,size_t) ; 

void
__pthread_distribute_static_tls(size_t offset, void *src, size_t len,
    size_t total_len)
{

	((void (*)(size_t, void *, size_t, size_t))__libc_interposing[
	    INTERPOS_distribute_static_tls])(offset, src, len, total_len);
}