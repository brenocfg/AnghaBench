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
typedef  int /*<<< orphan*/  u16 ;
struct admhcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc16 ;

/* Variables and functions */
 scalar_t__ big_endian_desc (struct admhcd const*) ; 
 int /*<<< orphan*/  cpu_to_be16p (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cpu_to_le16p (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline __hc16 cpu_to_hc16p(const struct admhcd *ahcd, const u16 *x)
{
	return big_endian_desc(ahcd) ?
		cpu_to_be16p(x) :
		cpu_to_le16p(x);
}