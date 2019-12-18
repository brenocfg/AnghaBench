#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ST_SR; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* CtlTempoTick ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* Handler ) (TYPE_1__*,unsigned int volatile) ;int /*<<< orphan*/  eot; } ;
typedef  int /*<<< orphan*/  AT91PS_USART ;

/* Variables and functions */
 scalar_t__ AT91C_BASE_DBGU ; 
 TYPE_5__* AT91C_BASE_ST ; 
 int /*<<< orphan*/ * AT91C_DBGU_CR ; 
 unsigned int* AT91C_DBGU_CSR ; 
 unsigned int volatile AT91C_US_ENDRX ; 
 unsigned int volatile AT91C_US_ENDTX ; 
 int /*<<< orphan*/  AT91C_US_RSTSTA ; 
 unsigned int volatile AT91C_US_RXBUFF ; 
 unsigned int volatile AT91C_US_RXRDY ; 
 unsigned int volatile AT91C_US_TIMEOUT ; 
 unsigned int volatile AT91C_US_TXEMPTY ; 
 unsigned int volatile AT91C_US_TXRDY ; 
 int /*<<< orphan*/  AT91F_US_DisableIt (int /*<<< orphan*/ ,unsigned int volatile) ; 
 int /*<<< orphan*/  AT91F_US_EnableIt (int /*<<< orphan*/ ,unsigned int volatile) ; 
 unsigned int AT91F_US_Error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StTick ; 
 TYPE_3__ ctlTempo ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,unsigned int volatile) ; 
 TYPE_1__ svcXmodem ; 

void AT91F_ST_HANDLER(void)
{
	volatile unsigned int csr = *AT91C_DBGU_CSR;
#ifdef XMODEM
	unsigned int error;
#endif
	
	if (AT91C_BASE_ST->ST_SR & 0x01) {
		StTick++;
		ctlTempo.CtlTempoTick(&ctlTempo);
		return;
	}

#ifdef XMODEM
	error = AT91F_US_Error((AT91PS_USART)AT91C_BASE_DBGU);
	if (csr & error) {
		/* Stop previous Xmodem transmition*/
		*(AT91C_DBGU_CR) = AT91C_US_RSTSTA;
		AT91F_US_DisableIt((AT91PS_USART)AT91C_BASE_DBGU, AT91C_US_ENDRX);
		AT91F_US_EnableIt((AT91PS_USART)AT91C_BASE_DBGU, AT91C_US_RXRDY);

	}
	
	else if (csr & (AT91C_US_TXRDY | AT91C_US_ENDTX | AT91C_US_TXEMPTY | 
	                AT91C_US_RXRDY | AT91C_US_ENDRX | AT91C_US_TIMEOUT | 
	                AT91C_US_RXBUFF)) {
		if ( !(svcXmodem.eot) )
			svcXmodem.Handler(&svcXmodem, csr);
	}
#endif
}