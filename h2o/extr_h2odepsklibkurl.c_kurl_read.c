#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t ssize_t ;
struct TYPE_4__ {scalar_t__ l_buf; size_t p_buf; size_t buf; } ;
typedef  TYPE_1__ kurl_t ;

/* Variables and functions */
 int fill_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,size_t,size_t) ; 

ssize_t kurl_read(kurl_t *ku, void *buf, size_t nbytes)
{
	ssize_t rest = nbytes;
	if (ku->l_buf == 0) return 0; // end-of-file
	while (rest) {
		if (ku->l_buf - ku->p_buf >= rest) {
			if (buf) memcpy((uint8_t*)buf + (nbytes - rest), ku->buf + ku->p_buf, rest);
			ku->p_buf += rest;
			rest = 0;
		} else {
			int ret;
			if (buf && ku->l_buf > ku->p_buf)
				memcpy((uint8_t*)buf + (nbytes - rest), ku->buf + ku->p_buf, ku->l_buf - ku->p_buf);
			rest -= ku->l_buf - ku->p_buf;
			ku->p_buf = ku->l_buf;
			ret = fill_buffer(ku);
			if (ret <= 0) break;
		}
	}
	return nbytes - rest;
}