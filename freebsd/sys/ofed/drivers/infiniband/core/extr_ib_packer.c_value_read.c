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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be64_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static u64 value_read(int offset, int size, void *structure)
{
	switch (size) {
	case 1: return                *(u8  *) ((char *)structure + offset);
	case 2: return be16_to_cpup((__be16 *) ((char *)structure + offset));
	case 4: return be32_to_cpup((__be32 *) ((char *)structure + offset));
	case 8: return be64_to_cpup((__be64 *) ((char *)structure + offset));
	default:
		pr_warn("Field size %d bits not handled\n", size * 8);
		return 0;
	}
}