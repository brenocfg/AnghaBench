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
struct gf128 {int /*<<< orphan*/ * v; } ;

/* Variables and functions */
 int /*<<< orphan*/  be64enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
gf128_write(struct gf128 v, uint8_t *buf)
{
	uint64_t tmp;

	be64enc(buf, v.v[0]);
	buf += sizeof tmp;

	be64enc(buf, v.v[1]);
}