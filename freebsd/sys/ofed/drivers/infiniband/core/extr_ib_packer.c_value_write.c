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
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static void value_write(int offset, int size, u64 val, void *structure)
{
	switch (size * 8) {
	case 8:  *(    u8 *) ((char *)structure + offset) = val; break;
	case 16: *(__be16 *) ((char *)structure + offset) = cpu_to_be16(val); break;
	case 32: *(__be32 *) ((char *)structure + offset) = cpu_to_be32(val); break;
	case 64: *(__be64 *) ((char *)structure + offset) = cpu_to_be64(val); break;
	default:
		pr_warn("Field size %d bits not handled\n", size * 8);
	}
}