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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct QBUFFER {int data_len; scalar_t__ data; } ;
struct AdapterControlBlock {int acb_flags; size_t wqbuf_firstindex; size_t wqbuf_lastindex; int /*<<< orphan*/ * wqbuffer; } ;

/* Variables and functions */
 int ACB_F_MESSAGE_WQBUFFER_READ ; 
 size_t ARCMSR_MAX_QBUFFER ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct QBUFFER* arcmsr_get_iop_wqbuffer (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_message_wrote (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arcmsr_Write_data_2iop_wqbuffer_D(struct AdapterControlBlock *acb)
{
	u_int8_t *pQbuffer;
	struct QBUFFER *pwbuffer;
	u_int8_t *buf1 = NULL;
	u_int32_t *iop_data, *buf2 = NULL;
	u_int32_t allxfer_len = 0, data_len;

	if(acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_READ) {
		buf1 = malloc(128, M_DEVBUF, M_NOWAIT | M_ZERO);
		buf2 = (u_int32_t *)buf1;
		if( buf1 == NULL)
			return;

		acb->acb_flags &= (~ACB_F_MESSAGE_WQBUFFER_READ);
		pwbuffer = arcmsr_get_iop_wqbuffer(acb);
		iop_data = (u_int32_t *)pwbuffer->data;
		while((acb->wqbuf_firstindex != acb->wqbuf_lastindex) 
			&& (allxfer_len < 124)) {
			pQbuffer = &acb->wqbuffer[acb->wqbuf_firstindex];
			*buf1 = *pQbuffer;
			acb->wqbuf_firstindex++;
			acb->wqbuf_firstindex %= ARCMSR_MAX_QBUFFER;
			buf1++;
			allxfer_len++;
		}
		pwbuffer->data_len = allxfer_len;
		data_len = allxfer_len;
		buf1 = (u_int8_t *)buf2;
		while(data_len >= 4)
		{
			*iop_data++ = *buf2++;
			data_len -= 4;
		}
		if(data_len)
			*iop_data = *buf2;
		free( buf1, M_DEVBUF);
		arcmsr_iop_message_wrote(acb);
	}
}