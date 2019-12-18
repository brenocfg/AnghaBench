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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 size_t MIN (size_t,scalar_t__) ; 
 scalar_t__ RSBUFSZ ; 
 int /*<<< orphan*/  _rs_rekey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rs_stir_if_needed (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ rs_buf ; 
 scalar_t__ rs_have ; 

__attribute__((used)) static inline void
_rs_random_buf(void *_buf, size_t n)
{
	u_char *buf = (u_char *)_buf;
	size_t m;

	_rs_stir_if_needed(n);
	while (n > 0) {
		if (rs_have > 0) {
			m = MIN(n, rs_have);
			memcpy(buf, rs_buf + RSBUFSZ - rs_have, m);
			memset(rs_buf + RSBUFSZ - rs_have, 0, m);
			buf += m;
			n -= m;
			rs_have -= m;
		}
		if (rs_have == 0)
			_rs_rekey(NULL, 0);
	}
}