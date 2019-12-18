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
struct mthca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_cqe(struct mthca_dev *dev, void *cqe_ptr)
{
	__be32 *cqe = cqe_ptr;

	(void) cqe;	/* avoid warning if mthca_dbg compiled away... */
	mthca_dbg(dev, "CQE contents %08x %08x %08x %08x %08x %08x %08x %08x\n",
		  be32_to_cpu(cqe[0]), be32_to_cpu(cqe[1]), be32_to_cpu(cqe[2]),
		  be32_to_cpu(cqe[3]), be32_to_cpu(cqe[4]), be32_to_cpu(cqe[5]),
		  be32_to_cpu(cqe[6]), be32_to_cpu(cqe[7]));
}