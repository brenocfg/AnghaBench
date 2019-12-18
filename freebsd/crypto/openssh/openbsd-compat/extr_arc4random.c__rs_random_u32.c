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
typedef  int /*<<< orphan*/  u_int32_t ;

/* Variables and functions */
 scalar_t__ RSBUFSZ ; 
 int /*<<< orphan*/  _rs_rekey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rs_stir_if_needed (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rs_buf ; 
 int rs_have ; 

__attribute__((used)) static inline void
_rs_random_u32(u_int32_t *val)
{
	_rs_stir_if_needed(sizeof(*val));
	if (rs_have < sizeof(*val))
		_rs_rekey(NULL, 0);
	memcpy(val, rs_buf + RSBUFSZ - rs_have, sizeof(*val));
	memset(rs_buf + RSBUFSZ - rs_have, 0, sizeof(*val));
	rs_have -= sizeof(*val);
	return;
}