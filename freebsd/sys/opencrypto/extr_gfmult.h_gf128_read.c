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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct gf128 {void** v; } ;

/* Variables and functions */
 void* be64dec (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline struct gf128
gf128_read(const uint8_t *buf)
{
	struct gf128 r;

	r.v[0] = be64dec(buf);
	buf += sizeof(uint64_t);

	r.v[1] = be64dec(buf);

	return r;
}