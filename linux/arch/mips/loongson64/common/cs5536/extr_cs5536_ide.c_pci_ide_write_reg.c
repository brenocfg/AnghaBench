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

/* Variables and functions */
 int CS5536_IDE_FLASH_SIGNATURE ; 
 int /*<<< orphan*/  DIVIL_BALL_OPTS ; 
 int /*<<< orphan*/  DIVIL_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLCP_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLCP_SOFT_COM ; 
 int /*<<< orphan*/  GLIU_IOD_BM2 ; 
 int /*<<< orphan*/  GLIU_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLIU_PAE ; 
 int /*<<< orphan*/  IDE_CAST ; 
 int /*<<< orphan*/  IDE_CFG ; 
 int /*<<< orphan*/  IDE_DTC ; 
 int /*<<< orphan*/  IDE_ETC ; 
 int /*<<< orphan*/  IDE_INTERNAL_PM ; 
 int /*<<< orphan*/  IDE_IO_BAR ; 
 int /*<<< orphan*/  IDE_MSR_REG (int /*<<< orphan*/ ) ; 
#define  PCI_BAR4_REG 136 
 int PCI_BAR_RANGE_MASK ; 
#define  PCI_CACHE_LINE_SIZE 135 
#define  PCI_COMMAND 134 
 int PCI_COMMAND_MASTER ; 
#define  PCI_IDE_CAST_REG 133 
#define  PCI_IDE_CFG_REG 132 
#define  PCI_IDE_DTC_REG 131 
#define  PCI_IDE_ETC_REG 130 
#define  PCI_IDE_PM_REG 129 
#define  PCI_STATUS 128 
 int PCI_STATUS_PARITY ; 
 int /*<<< orphan*/  SB_CTRL ; 
 int /*<<< orphan*/  SB_ERROR ; 
 int /*<<< orphan*/  SB_MSR_REG (int /*<<< orphan*/ ) ; 
 int SB_PARE_ERR_FLAG ; 
 int SOFT_BAR_IDE_FLAG ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 

void pci_ide_write_reg(int reg, u32 value)
{
	u32 hi = 0, lo = value;

	switch (reg) {
	case PCI_COMMAND:
		_rdmsr(GLIU_MSR_REG(GLIU_PAE), &hi, &lo);
		if (value & PCI_COMMAND_MASTER)
			lo |= (0x03 << 4);
		else
			lo &= ~(0x03 << 4);
		_wrmsr(GLIU_MSR_REG(GLIU_PAE), hi, lo);
		break;
	case PCI_STATUS:
		if (value & PCI_STATUS_PARITY) {
			_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
			if (lo & SB_PARE_ERR_FLAG) {
				lo = (lo & 0x0000ffff) | SB_PARE_ERR_FLAG;
				_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
			}
		}
		break;
	case PCI_CACHE_LINE_SIZE:
		value &= 0x0000ff00;
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0xffffff00;
		hi |= (value >> 8);
		_wrmsr(SB_MSR_REG(SB_CTRL), hi, lo);
		break;
	case PCI_BAR4_REG:
		if (value == PCI_BAR_RANGE_MASK) {
			_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
			lo |= SOFT_BAR_IDE_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		} else if (value & 0x01) {
			_rdmsr(IDE_MSR_REG(IDE_IO_BAR), &hi, &lo);
			lo = (value & 0xfffffff0) | 0x1;
			_wrmsr(IDE_MSR_REG(IDE_IO_BAR), hi, lo);

			value &= 0xfffffffc;
			hi = 0x60000000 | ((value & 0x000ff000) >> 12);
			lo = 0x000ffff0 | ((value & 0x00000fff) << 20);
			_wrmsr(GLIU_MSR_REG(GLIU_IOD_BM2), hi, lo);
		}
		break;
	case PCI_IDE_CFG_REG:
		if (value == CS5536_IDE_FLASH_SIGNATURE) {
			_rdmsr(DIVIL_MSR_REG(DIVIL_BALL_OPTS), &hi, &lo);
			lo |= 0x01;
			_wrmsr(DIVIL_MSR_REG(DIVIL_BALL_OPTS), hi, lo);
		} else {
			_rdmsr(IDE_MSR_REG(IDE_CFG), &hi, &lo);
			lo = value;
			_wrmsr(IDE_MSR_REG(IDE_CFG), hi, lo);
		}
		break;
	case PCI_IDE_DTC_REG:
		_rdmsr(IDE_MSR_REG(IDE_DTC), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_DTC), hi, lo);
		break;
	case PCI_IDE_CAST_REG:
		_rdmsr(IDE_MSR_REG(IDE_CAST), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_CAST), hi, lo);
		break;
	case PCI_IDE_ETC_REG:
		_rdmsr(IDE_MSR_REG(IDE_ETC), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_ETC), hi, lo);
		break;
	case PCI_IDE_PM_REG:
		_rdmsr(IDE_MSR_REG(IDE_INTERNAL_PM), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_INTERNAL_PM), hi, lo);
		break;
	default:
		break;
	}
}