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
struct spi_slave {unsigned int bus; unsigned int cs; } ;
struct ar71xx_spi_slave {unsigned int mode; struct spi_slave slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRINTD (char*) ; 
 struct ar71xx_spi_slave* malloc (int) ; 

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int mode)
{
	struct ar71xx_spi_slave *ss;

	PRINTD("ar71xx_spi: spi_setup_slave");
	
	if ((bus != 0) || (cs > 2))
		return NULL;

	ss = malloc(sizeof(struct ar71xx_spi_slave));
	if (!ss)
		return NULL;

	ss->slave.bus = bus;
	ss->slave.cs = cs;
	ss->mode = mode;

	/* TODO: Use max_hz to limit the SCK rate */

	PRINTD(" ---> out\n");
	
	return &ss->slave;
}