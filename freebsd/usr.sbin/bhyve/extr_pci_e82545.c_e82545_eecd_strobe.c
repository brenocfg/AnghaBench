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
typedef  scalar_t__ uint16_t ;
struct e82545_softc {scalar_t__ nvm_bits; void* nvm_mode; scalar_t__ nvm_opaddr; int nvm_data; int eeprom_control; int* eeprom_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,void*,...) ; 
 int E1000_EECD_DI ; 
 int E1000_EECD_DO ; 
 scalar_t__ E82545_NVM_ADDR_MASK ; 
 void* E82545_NVM_DATA_BITS ; 
 scalar_t__ E82545_NVM_EEPROM_SIZE ; 
 void* E82545_NVM_MODE_DATAIN ; 
 void* E82545_NVM_MODE_DATAOUT ; 
 void* E82545_NVM_MODE_OPADDR ; 
 void* E82545_NVM_OPADDR_BITS ; 
#define  E82545_NVM_OPCODE_EWEN 130 
 scalar_t__ E82545_NVM_OPCODE_MASK ; 
#define  E82545_NVM_OPCODE_READ 129 
#define  E82545_NVM_OPCODE_WRITE 128 

__attribute__((used)) static void
e82545_eecd_strobe(struct e82545_softc *sc)
{
	/* Microwire state machine */
	/*
	DPRINTF("eeprom state machine srtobe "
		"0x%x 0x%x 0x%x 0x%x\r\n",
		sc->nvm_mode, sc->nvm_bits,
		sc->nvm_opaddr, sc->nvm_data);*/

	if (sc->nvm_bits == 0) {
		DPRINTF("eeprom state machine not expecting data! "
			"0x%x 0x%x 0x%x 0x%x\r\n",
			sc->nvm_mode, sc->nvm_bits,
			sc->nvm_opaddr, sc->nvm_data);
		return;
	}
	sc->nvm_bits--;
	if (sc->nvm_mode == E82545_NVM_MODE_DATAOUT) {
		/* shifting out */
		if (sc->nvm_data & 0x8000) {
			sc->eeprom_control |= E1000_EECD_DO;
		} else {
			sc->eeprom_control &= ~E1000_EECD_DO;
		}
		sc->nvm_data <<= 1;
		if (sc->nvm_bits == 0) {
			/* read done, back to opcode mode. */
			sc->nvm_opaddr = 0;
			sc->nvm_mode = E82545_NVM_MODE_OPADDR;
			sc->nvm_bits = E82545_NVM_OPADDR_BITS;
		}
	} else if (sc->nvm_mode == E82545_NVM_MODE_DATAIN) {
		/* shifting in */
		sc->nvm_data <<= 1;
		if (sc->eeprom_control & E1000_EECD_DI) {
			sc->nvm_data |= 1;
		}
		if (sc->nvm_bits == 0) {
			/* eeprom write */
			uint16_t op = sc->nvm_opaddr & E82545_NVM_OPCODE_MASK;
			uint16_t addr = sc->nvm_opaddr & E82545_NVM_ADDR_MASK;
			if (op != E82545_NVM_OPCODE_WRITE) {
				DPRINTF("Illegal eeprom write op 0x%x\r\n",
					sc->nvm_opaddr);
			} else if (addr >= E82545_NVM_EEPROM_SIZE) {
				DPRINTF("Illegal eeprom write addr 0x%x\r\n",
					sc->nvm_opaddr);
			} else {
				DPRINTF("eeprom write eeprom[0x%x] = 0x%x\r\n",
				addr, sc->nvm_data);
				sc->eeprom_data[addr] = sc->nvm_data;
			}
			/* back to opcode mode */
			sc->nvm_opaddr = 0;
			sc->nvm_mode = E82545_NVM_MODE_OPADDR;
			sc->nvm_bits = E82545_NVM_OPADDR_BITS;
		}
	} else if (sc->nvm_mode == E82545_NVM_MODE_OPADDR) {
		sc->nvm_opaddr <<= 1;
		if (sc->eeprom_control & E1000_EECD_DI) {
			sc->nvm_opaddr |= 1;
		}
		if (sc->nvm_bits == 0) {
			uint16_t op = sc->nvm_opaddr & E82545_NVM_OPCODE_MASK;
			switch (op) {
			case E82545_NVM_OPCODE_EWEN:
				DPRINTF("eeprom write enable: 0x%x\r\n",
					sc->nvm_opaddr);
				/* back to opcode mode */
				sc->nvm_opaddr = 0;
				sc->nvm_mode = E82545_NVM_MODE_OPADDR;
				sc->nvm_bits = E82545_NVM_OPADDR_BITS;
				break;
			case E82545_NVM_OPCODE_READ:
			{
				uint16_t addr = sc->nvm_opaddr &
					E82545_NVM_ADDR_MASK;
				sc->nvm_mode = E82545_NVM_MODE_DATAOUT;
				sc->nvm_bits = E82545_NVM_DATA_BITS;
				if (addr < E82545_NVM_EEPROM_SIZE) {
					sc->nvm_data = sc->eeprom_data[addr];
					DPRINTF("eeprom read: eeprom[0x%x] = 0x%x\r\n",
						addr, sc->nvm_data);
				} else {
					DPRINTF("eeprom illegal read: 0x%x\r\n",
						sc->nvm_opaddr);
					sc->nvm_data = 0;
				}
				break;
			}
			case E82545_NVM_OPCODE_WRITE:
				sc->nvm_mode = E82545_NVM_MODE_DATAIN;
				sc->nvm_bits = E82545_NVM_DATA_BITS;
				sc->nvm_data = 0;
				break;
			default:
				DPRINTF("eeprom unknown op: 0x%x\r\r",
					sc->nvm_opaddr);
				/* back to opcode mode */
				sc->nvm_opaddr = 0;
				sc->nvm_mode = E82545_NVM_MODE_OPADDR;
				sc->nvm_bits = E82545_NVM_OPADDR_BITS;
			}
		}
	} else {
		DPRINTF("eeprom state machine wrong state! "
			"0x%x 0x%x 0x%x 0x%x\r\n",
			sc->nvm_mode, sc->nvm_bits,
			sc->nvm_opaddr, sc->nvm_data);
	}
}