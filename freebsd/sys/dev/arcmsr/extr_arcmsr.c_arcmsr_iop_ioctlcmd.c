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
typedef  char u_int8_t ;
typedef  int u_int32_t ;
struct QBUFFER {int dummy; } ;
struct TYPE_2__ {int Length; void* ReturnCode; int /*<<< orphan*/  Signature; } ;
struct CMD_MESSAGE_FIELD {char* messagedatabuffer; TYPE_1__ cmdmessage; } ;
struct AdapterControlBlock {size_t rqbuf_firstindex; size_t rqbuf_lastindex; char* rqbuffer; int acb_flags; int wqbuf_lastindex; int wqbuf_firstindex; char* wqbuffer; int /*<<< orphan*/  qbuffer_lock; } ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ACB_F_IOPDATA_OVERFLOW ; 
 int ACB_F_MESSAGE_RQBUFFER_CLEARED ; 
 int ACB_F_MESSAGE_WQBUFFER_CLEARED ; 
 int ACB_F_MESSAGE_WQBUFFER_READ ; 
 int /*<<< orphan*/  ARCMSR_LOCK_ACQUIRE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARCMSR_LOCK_RELEASE (int /*<<< orphan*/ *) ; 
 int ARCMSR_MAX_QBUFFER ; 
#define  ARCMSR_MESSAGE_CLEAR_ALLQBUFFER 136 
#define  ARCMSR_MESSAGE_CLEAR_RQBUFFER 135 
#define  ARCMSR_MESSAGE_CLEAR_WQBUFFER 134 
#define  ARCMSR_MESSAGE_FLUSH_ADAPTER_CACHE 133 
#define  ARCMSR_MESSAGE_READ_RQBUFFER 132 
#define  ARCMSR_MESSAGE_REQUEST_RETURNCODE_3F 131 
 void* ARCMSR_MESSAGE_RETURNCODE_3F ; 
 void* ARCMSR_MESSAGE_RETURNCODE_ERROR ; 
 void* ARCMSR_MESSAGE_RETURNCODE_OK ; 
#define  ARCMSR_MESSAGE_SAY_GOODBYE 130 
#define  ARCMSR_MESSAGE_SAY_HELLO 129 
 int ARCMSR_MESSAGE_SUCCESS ; 
#define  ARCMSR_MESSAGE_WRITE_WQBUFFER 128 
 int EINVAL ; 
 int ENOIOCTL ; 
 int /*<<< orphan*/  arcmsr_Read_iop_rqbuffer_data (struct AdapterControlBlock*,struct QBUFFER*) ; 
 int /*<<< orphan*/  arcmsr_Write_data_2iop_wqbuffer (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_adapter_cache (struct AdapterControlBlock*) ; 
 struct QBUFFER* arcmsr_get_iop_rqbuffer (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_message_read (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_iop_parking (struct AdapterControlBlock*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static u_int32_t arcmsr_iop_ioctlcmd(struct AdapterControlBlock *acb, u_int32_t ioctl_cmd, caddr_t arg)
{
	struct CMD_MESSAGE_FIELD *pcmdmessagefld;
	u_int32_t retvalue = EINVAL;

	pcmdmessagefld = (struct CMD_MESSAGE_FIELD *) arg;
	if(memcmp(pcmdmessagefld->cmdmessage.Signature, "ARCMSR", 6)!=0) {
		return retvalue;
	}
	ARCMSR_LOCK_ACQUIRE(&acb->qbuffer_lock);
	switch(ioctl_cmd) {
	case ARCMSR_MESSAGE_READ_RQBUFFER: {
			u_int8_t *pQbuffer;
			u_int8_t *ptmpQbuffer = pcmdmessagefld->messagedatabuffer;			
			u_int32_t allxfer_len=0;

			while((acb->rqbuf_firstindex != acb->rqbuf_lastindex) 
				&& (allxfer_len < 1031)) {
				/*copy READ QBUFFER to srb*/
				pQbuffer = &acb->rqbuffer[acb->rqbuf_firstindex];
				*ptmpQbuffer = *pQbuffer;
				acb->rqbuf_firstindex++;
				acb->rqbuf_firstindex %= ARCMSR_MAX_QBUFFER; 
				/*if last index number set it to 0 */
				ptmpQbuffer++;
				allxfer_len++;
			}
			if(acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) {
				struct QBUFFER *prbuffer;

				acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
				prbuffer = arcmsr_get_iop_rqbuffer(acb);
				if(arcmsr_Read_iop_rqbuffer_data(acb, prbuffer) == 0)
					acb->acb_flags |= ACB_F_IOPDATA_OVERFLOW;
			}
			pcmdmessagefld->cmdmessage.Length = allxfer_len;
			pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_OK;
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_WRITE_WQBUFFER: {
			u_int32_t my_empty_len, user_len, wqbuf_firstindex, wqbuf_lastindex;
			u_int8_t *pQbuffer;
			u_int8_t *ptmpuserbuffer = pcmdmessagefld->messagedatabuffer;

			user_len = pcmdmessagefld->cmdmessage.Length;
			/*check if data xfer length of this request will overflow my array qbuffer */
			wqbuf_lastindex = acb->wqbuf_lastindex;
			wqbuf_firstindex = acb->wqbuf_firstindex;
			if(wqbuf_lastindex != wqbuf_firstindex) {
				arcmsr_Write_data_2iop_wqbuffer(acb);
				pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_ERROR;
			} else {
				my_empty_len = (wqbuf_firstindex - wqbuf_lastindex - 1) &
					(ARCMSR_MAX_QBUFFER - 1);
				if(my_empty_len >= user_len) {
					while(user_len > 0) {
						/*copy srb data to wqbuffer*/
						pQbuffer = &acb->wqbuffer[acb->wqbuf_lastindex];
						*pQbuffer = *ptmpuserbuffer;
						acb->wqbuf_lastindex++;
						acb->wqbuf_lastindex %= ARCMSR_MAX_QBUFFER;
						/*if last index number set it to 0 */
						ptmpuserbuffer++;
						user_len--;
					}
					/*post fist Qbuffer*/
					if(acb->acb_flags & ACB_F_MESSAGE_WQBUFFER_CLEARED) {
						acb->acb_flags &= ~ACB_F_MESSAGE_WQBUFFER_CLEARED;
						arcmsr_Write_data_2iop_wqbuffer(acb);
					}
					pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_OK;
				} else {
					pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_ERROR;
				}
			}
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_CLEAR_RQBUFFER: {
			u_int8_t *pQbuffer = acb->rqbuffer;

			if(acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) {
				acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
				arcmsr_iop_message_read(acb);
				/*signature, let IOP know data has been readed */
			}
			acb->acb_flags |= ACB_F_MESSAGE_RQBUFFER_CLEARED;
			acb->rqbuf_firstindex = 0;
			acb->rqbuf_lastindex = 0;
			memset(pQbuffer, 0, ARCMSR_MAX_QBUFFER);
			pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_OK;
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_CLEAR_WQBUFFER:
		{
			u_int8_t *pQbuffer = acb->wqbuffer;

			if(acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) {
				acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
				arcmsr_iop_message_read(acb);
				/*signature, let IOP know data has been readed */
			}
			acb->acb_flags |= (ACB_F_MESSAGE_WQBUFFER_CLEARED|ACB_F_MESSAGE_WQBUFFER_READ);
			acb->wqbuf_firstindex = 0;
			acb->wqbuf_lastindex = 0;
			memset(pQbuffer, 0, ARCMSR_MAX_QBUFFER);
			pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_OK;
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_CLEAR_ALLQBUFFER: {
			u_int8_t *pQbuffer;

			if(acb->acb_flags & ACB_F_IOPDATA_OVERFLOW) {
				acb->acb_flags &= ~ACB_F_IOPDATA_OVERFLOW;
				arcmsr_iop_message_read(acb);
				/*signature, let IOP know data has been readed */
			}
			acb->acb_flags  |= (ACB_F_MESSAGE_WQBUFFER_CLEARED
					|ACB_F_MESSAGE_RQBUFFER_CLEARED
					|ACB_F_MESSAGE_WQBUFFER_READ);
			acb->rqbuf_firstindex = 0;
			acb->rqbuf_lastindex = 0;
			acb->wqbuf_firstindex = 0;
			acb->wqbuf_lastindex = 0;
			pQbuffer = acb->rqbuffer;
			memset(pQbuffer, 0, sizeof(struct QBUFFER));
			pQbuffer = acb->wqbuffer;
			memset(pQbuffer, 0, sizeof(struct QBUFFER));
			pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_OK;
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_REQUEST_RETURNCODE_3F: {
			pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_3F;
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_SAY_HELLO: {
			u_int8_t *hello_string = "Hello! I am ARCMSR";
			u_int8_t *puserbuffer = (u_int8_t *)pcmdmessagefld->messagedatabuffer;

			if(memcpy(puserbuffer, hello_string, (int16_t)strlen(hello_string))) {
				pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_ERROR;
				ARCMSR_LOCK_RELEASE(&acb->qbuffer_lock);
				return ENOIOCTL;
			}
			pcmdmessagefld->cmdmessage.ReturnCode = ARCMSR_MESSAGE_RETURNCODE_OK;
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_SAY_GOODBYE: {
			arcmsr_iop_parking(acb);
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	case ARCMSR_MESSAGE_FLUSH_ADAPTER_CACHE: {
			arcmsr_flush_adapter_cache(acb);
			retvalue = ARCMSR_MESSAGE_SUCCESS;
		}
		break;
	}
	ARCMSR_LOCK_RELEASE(&acb->qbuffer_lock);
	return (retvalue);
}