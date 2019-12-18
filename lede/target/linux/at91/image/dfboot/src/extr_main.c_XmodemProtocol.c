#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* Start ) (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_5__ tempo; int /*<<< orphan*/  pUsart; } ;
struct TYPE_8__ {TYPE_1__* pBuffer; } ;
struct TYPE_7__ {scalar_t__ szRdBuffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  pChild; } ;
typedef  int /*<<< orphan*/  AT91S_PipeStatus ;
typedef  int /*<<< orphan*/  AT91PS_USART ;
typedef  TYPE_2__* AT91PS_SBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_XmodemComplete ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ svcXmodem ; 
 TYPE_3__ xmodemPipe ; 

__attribute__((used)) static void XmodemProtocol(AT91S_PipeStatus status, void *pVoid)
{
	AT91PS_SBuffer pSBuffer = (AT91PS_SBuffer) xmodemPipe.pBuffer->pChild;
	AT91PS_USART   pUsart     = svcXmodem.pUsart;
			
	if (pSBuffer->szRdBuffer == 0) {
		/* Start a tempo to wait the Xmodem protocol complete */
		svcXmodem.tempo.Start(&(svcXmodem.tempo), 10, 0, AT91_XmodemComplete, pUsart);								
	}
}