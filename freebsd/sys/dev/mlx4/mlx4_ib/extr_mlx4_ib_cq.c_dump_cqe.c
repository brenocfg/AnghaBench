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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_cqe(void *cqe)
{
	__be32 *buf = cqe;

	pr_debug("CQE contents %08x %08x %08x %08x %08x %08x %08x %08x\n",
	       be32_to_cpu(buf[0]), be32_to_cpu(buf[1]), be32_to_cpu(buf[2]),
	       be32_to_cpu(buf[3]), be32_to_cpu(buf[4]), be32_to_cpu(buf[5]),
	       be32_to_cpu(buf[6]), be32_to_cpu(buf[7]));
}