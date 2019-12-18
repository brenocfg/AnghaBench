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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct thread {int dummy; } ;
struct ppi_data {int /*<<< orphan*/  ppi_device; } ;
struct cdev {struct ppi_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENOTTY ; 
#define  PPIGCTRL 141 
#define  PPIGDATA 140 
#define  PPIGECR 139 
#define  PPIGEPPA 138 
#define  PPIGEPPD 137 
#define  PPIGFIFO 136 
#define  PPIGSTATUS 135 
#define  PPISCTRL 134 
#define  PPISDATA 133 
#define  PPISECR 132 
#define  PPISEPPA 131 
#define  PPISEPPD 130 
#define  PPISFIFO 129 
#define  PPISSTATUS 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_rctr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_rdtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_recr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_repp_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_repp_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_rfifo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wecr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wepp_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wepp_D (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wfifo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppiioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags, struct thread *td)
{
	struct ppi_data *ppi = dev->si_drv1;
	device_t ppidev = ppi->ppi_device;
	device_t ppbus = device_get_parent(ppidev);
	int error = 0;
	u_int8_t *val = (u_int8_t *)data;

	ppb_lock(ppbus);
	switch (cmd) {

	case PPIGDATA:			/* get data register */
		*val = ppb_rdtr(ppbus);
		break;
	case PPIGSTATUS:		/* get status bits */
		*val = ppb_rstr(ppbus);
		break;
	case PPIGCTRL:			/* get control bits */
		*val = ppb_rctr(ppbus);
		break;
	case PPIGEPPD:			/* get EPP data bits */
		*val = ppb_repp_D(ppbus);
		break;
	case PPIGECR:			/* get ECP bits */
		*val = ppb_recr(ppbus);
		break;
	case PPIGFIFO:			/* read FIFO */
		*val = ppb_rfifo(ppbus);
		break;
	case PPISDATA:			/* set data register */
		ppb_wdtr(ppbus, *val);
		break;
	case PPISSTATUS:		/* set status bits */
		ppb_wstr(ppbus, *val);
		break;
	case PPISCTRL:			/* set control bits */
		ppb_wctr(ppbus, *val);
		break;
	case PPISEPPD:			/* set EPP data bits */
		ppb_wepp_D(ppbus, *val);
		break;
	case PPISECR:			/* set ECP bits */
		ppb_wecr(ppbus, *val);
		break;
	case PPISFIFO:			/* write FIFO */
		ppb_wfifo(ppbus, *val);
		break;
	case PPIGEPPA:			/* get EPP address bits */
		*val = ppb_repp_A(ppbus);
		break;
	case PPISEPPA:			/* set EPP address bits */
		ppb_wepp_A(ppbus, *val);
		break;
	default:
		error = ENOTTY;
		break;
	}
	ppb_unlock(ppbus);

	return (error);
}