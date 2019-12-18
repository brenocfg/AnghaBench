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
struct stm32_hash_dev {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ HASH_SR ; 
 int HASH_SR_BUSY ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static inline int stm32_hash_wait_busy(struct stm32_hash_dev *hdev)
{
	u32 status;

	return readl_relaxed_poll_timeout(hdev->io_base + HASH_SR, status,
				   !(status & HASH_SR_BUSY), 10, 10000);
}