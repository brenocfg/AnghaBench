#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_message {TYPE_1__* spi; int /*<<< orphan*/  queue; int /*<<< orphan*/  status; scalar_t__ actual_length; } ;
struct spi_device {int /*<<< orphan*/  master; } ;
struct rb4xx_spi {scalar_t__ cs_wait; int /*<<< orphan*/  lock; scalar_t__ busy; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {scalar_t__ chip_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb4xx_spi_process_queue_locked (struct rb4xx_spi*,unsigned long*) ; 
 struct rb4xx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rb4xx_spi_transfer(struct spi_device *spi,
			      struct spi_message *m)
{
	struct rb4xx_spi *rbspi = spi_master_get_devdata(spi->master);
	unsigned long flags;

	m->actual_length = 0;
	m->status = -EINPROGRESS;

	spin_lock_irqsave(&rbspi->lock, flags);
	list_add_tail(&m->queue, &rbspi->queue);
	if (rbspi->busy ||
	    (rbspi->cs_wait >= 0 && rbspi->cs_wait != m->spi->chip_select)) {
		/* job will be done later */
		spin_unlock_irqrestore(&rbspi->lock, flags);
		return 0;
	}

	/* process job in current context */
	rb4xx_spi_process_queue_locked(rbspi, &flags);
	spin_unlock_irqrestore(&rbspi->lock, flags);

	return 0;
}