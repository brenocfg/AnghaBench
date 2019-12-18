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
 uintptr_t _libc_get_static_tls_base (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

void
__libc_distribute_static_tls(size_t offset, void *src, size_t len,
    size_t total_len)
{
	uintptr_t tlsbase;

	tlsbase = _libc_get_static_tls_base(offset);
	memcpy((void *)tlsbase, src, len);
	memset((char *)tlsbase + len, 0, total_len - len);
}