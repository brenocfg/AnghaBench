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
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ ) ; 
 char const* decode_bitflags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  peer_st_bits ; 

__attribute__((used)) static const char *
peer_st_flags(
	u_char pst
	)
{
	return decode_bitflags(pst, ", ", peer_st_bits,
			       COUNTOF(peer_st_bits));
}