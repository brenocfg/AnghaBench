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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ p ;

/* Variables and functions */
 scalar_t__ ntohl (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline uint64_t
EXTRACT_64BITS(const void *p)
{
	return ((uint64_t)(((uint64_t)ntohl(*((const uint32_t *)(p) + 0))) << 32 | \
		((uint64_t)ntohl(*((const uint32_t *)(p) + 1))) << 0));

}