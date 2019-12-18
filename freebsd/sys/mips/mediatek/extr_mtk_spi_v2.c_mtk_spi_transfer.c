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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; int tx_data_sz; int rx_data_sz; scalar_t__ rx_data; scalar_t__ tx_data; scalar_t__ tx_cmd; scalar_t__ rx_cmd; } ;
struct mtk_spi_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  CMD_ENTER_4B_MODE 137 
#define  CMD_EXIT_4B_MODE 136 
#define  CMD_FAST_READ 135 
#define  CMD_PAGE_PROGRAM 134 
#define  CMD_READ 133 
#define  CMD_READ_IDENT 132 
#define  CMD_READ_STATUS 131 
#define  CMD_SECTOR_ERASE 130 
#define  CMD_WRITE_DISABLE 129 
#define  CMD_WRITE_ENABLE 128 
 int ENXIO ; 
 int /*<<< orphan*/  MTK_SPI_READ ; 
 int /*<<< orphan*/  MTK_SPI_WRITE ; 
 int /*<<< orphan*/  SPIBUS_CS_HIGH ; 
 struct mtk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_spi_chip_activate (struct mtk_spi_softc*) ; 
 int /*<<< orphan*/  mtk_spi_chip_deactivate (struct mtk_spi_softc*) ; 
 int mtk_spi_txrx (struct mtk_spi_softc*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spibus_get_cs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mtk_spi_transfer(device_t dev, device_t child, struct spi_command *cmd)
{
	struct mtk_spi_softc *sc;
	uint8_t *buf, byte, *tx_buf;
	uint32_t cs;
	int i, sz, error, write = 0;

	sc = device_get_softc(dev);

	spibus_get_cs(child, &cs);

	cs &= ~SPIBUS_CS_HIGH;

	if (cs != 0)
		/* Only 1 CS */
		return (ENXIO);

        /* There is always a command to transfer. */
        tx_buf = (uint8_t *)(cmd->tx_cmd);

        /* Perform some fixup because MTK dont support duplex SPI */
        switch(tx_buf[0]) {
                case CMD_READ_IDENT:
                        cmd->tx_cmd_sz = 1;
                        cmd->rx_cmd_sz = 3;
                        break;
		case CMD_ENTER_4B_MODE:
		case CMD_EXIT_4B_MODE:
                case CMD_WRITE_ENABLE:
                case CMD_WRITE_DISABLE:
                        cmd->tx_cmd_sz = 1;
                        cmd->rx_cmd_sz = 0;
                        break;
                case CMD_READ_STATUS:
                        cmd->tx_cmd_sz = 1;
                        cmd->rx_cmd_sz = 1;
                        break;
                case CMD_READ:
                case CMD_FAST_READ:
                        cmd->rx_cmd_sz = cmd->tx_data_sz = 0;
                        break;
                case CMD_SECTOR_ERASE:
                        cmd->rx_cmd_sz = 0;
                        break;
                case CMD_PAGE_PROGRAM:
                        cmd->rx_cmd_sz = cmd->rx_data_sz = 0;
                        break;
        }      
        
	mtk_spi_chip_activate(sc);

	if (cmd->tx_cmd_sz + cmd->rx_cmd_sz) {
		buf = (uint8_t *)(cmd->rx_cmd);
		tx_buf = (uint8_t *)(cmd->tx_cmd);
		sz = cmd->tx_cmd_sz + cmd->rx_cmd_sz;

		for (i = 0; i < sz; i++) {
                        if(i < cmd->tx_cmd_sz) {
			        byte = tx_buf[i];
        			error = mtk_spi_txrx(sc, &byte,
		        	    MTK_SPI_WRITE);
				if (error)
					goto mtk_spi_transfer_fail;
				continue;
                        }
                        error = mtk_spi_txrx(sc, &byte,
		            MTK_SPI_READ);
			if (error)
				goto mtk_spi_transfer_fail;
			buf[i] = byte;
		}
	}
	
	/*
	 * Transfer/Receive data
	 */
	
	if (cmd->tx_data_sz + cmd->rx_data_sz) {
		write = (cmd->tx_data_sz > 0)?1:0;
		buf = (uint8_t *)(write ? cmd->tx_data : cmd->rx_data);
		sz = write ? cmd->tx_data_sz : cmd->rx_data_sz;

		for (i = 0; i < sz; i++) {
			byte = buf[i];
			error = mtk_spi_txrx(sc, &byte,
			    write ? MTK_SPI_WRITE : MTK_SPI_READ);
			if (error)
				goto mtk_spi_transfer_fail;
			buf[i] = byte;
		}
	}
mtk_spi_transfer_fail:
	mtk_spi_chip_deactivate(sc);

	return (0);
}