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
struct s5p_aes_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSS_HASH_FIFO_MODE_DMA ; 
 int /*<<< orphan*/  SSS_REG_HASH_CTRL_FIFO ; 
 int /*<<< orphan*/  s5p_hash_write (struct s5p_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_hash_dma_enable(struct s5p_aes_dev *dev)
{
	s5p_hash_write(dev, SSS_REG_HASH_CTRL_FIFO, SSS_HASH_FIFO_MODE_DMA);
}