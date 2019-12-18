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
typedef  int u32 ;
struct hwicap_drvdata {scalar_t__ base_address; } ;

/* Variables and functions */
 int XHI_SR_DONE_MASK ; 
 scalar_t__ XHI_SR_OFFSET ; 
 int in_be32 (scalar_t__) ; 

__attribute__((used)) static inline u32 fifo_icap_busy(struct hwicap_drvdata *drvdata)
{
	u32 status = in_be32(drvdata->base_address + XHI_SR_OFFSET);
	return (status & XHI_SR_DONE_MASK) ? 0 : 1;
}