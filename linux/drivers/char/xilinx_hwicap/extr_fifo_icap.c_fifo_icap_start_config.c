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
struct hwicap_drvdata {int /*<<< orphan*/  dev; scalar_t__ base_address; } ;

/* Variables and functions */
 scalar_t__ XHI_CR_OFFSET ; 
 int /*<<< orphan*/  XHI_CR_WRITE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fifo_icap_start_config(struct hwicap_drvdata *drvdata)
{
	out_be32(drvdata->base_address + XHI_CR_OFFSET, XHI_CR_WRITE_MASK);
	dev_dbg(drvdata->dev, "configuration started\n");
}