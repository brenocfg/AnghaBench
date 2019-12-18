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
typedef  int /*<<< orphan*/  u32 ;
struct admhcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc32 ;

/* Variables and functions */
 scalar_t__ big_endian_desc (struct admhcd const*) ; 
 int /*<<< orphan*/  cpu_to_be32p (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cpu_to_le32p (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline __hc32 cpu_to_hc32p(const struct admhcd *ahcd, const u32 *x)
{
	return big_endian_desc(ahcd) ?
		cpu_to_be32p(x) :
		cpu_to_le32p(x);
}