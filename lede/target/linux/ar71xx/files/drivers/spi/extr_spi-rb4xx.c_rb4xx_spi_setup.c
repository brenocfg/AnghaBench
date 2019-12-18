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
struct spi_device {int mode; int bits_per_word; int chip_select; int /*<<< orphan*/  dev; int /*<<< orphan*/  master; } ;
struct rb4xx_spi {int cs_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_CS_HIGH ; 
 int SPI_TX_DUAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  rb4xx_spi_process_queue_locked (struct rb4xx_spi*,unsigned long*) ; 
 struct rb4xx_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rb4xx_spi_setup(struct spi_device *spi)
{
	struct rb4xx_spi *rbspi = spi_master_get_devdata(spi->master);
	unsigned long flags;

	if (spi->mode & ~(SPI_CS_HIGH | SPI_TX_DUAL)) {
		dev_err(&spi->dev, "mode %x not supported\n",
			(unsigned) spi->mode);
		return -EINVAL;
	}

	if (spi->bits_per_word != 8 && spi->bits_per_word != 0) {
		dev_err(&spi->dev, "bits_per_word %u not supported\n",
			(unsigned) spi->bits_per_word);
		return -EINVAL;
	}

	spin_lock_irqsave(&rbspi->lock, flags);
	if (rbspi->cs_wait == spi->chip_select && !rbspi->busy) {
		rbspi->cs_wait = -1;
		rb4xx_spi_process_queue_locked(rbspi, &flags);
	}
	spin_unlock_irqrestore(&rbspi->lock, flags);

	return 0;
}