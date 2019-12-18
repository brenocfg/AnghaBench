#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_6__ {int adapterId; } ;
struct TYPE_8__ {int /*<<< orphan*/  VBus; TYPE_1__ mvSataAdapter; struct TYPE_8__* next; } ;
struct TYPE_7__ {scalar_t__ Magic; scalar_t__ nInBufferSize; scalar_t__ nOutBufferSize; scalar_t__ lpBytesReturned; scalar_t__ lpOutBuffer; int /*<<< orphan*/  dwIoControlCode; scalar_t__ lpInBuffer; } ;
typedef  int /*<<< orphan*/ * PUCHAR ;
typedef  TYPE_2__* PHPT_IOCTL_PARAM ;
typedef  TYPE_3__ IAL_ADAPTER_T ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ HPT_IOCTL_MAGIC ; 
 scalar_t__ HPT_IOCTL_MAGIC32 ; 
 int /*<<< orphan*/  KdPrintE (char*) ; 
 int /*<<< orphan*/  KdPrintW (char*) ; 
 int Kernel_DeviceIoControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ copyin (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* gIal_Adapter ; 
 int hpt_set_asc_info (TYPE_3__*,char*,int) ; 
 char* hptproc_buffer ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
hpt_set_info(int length)
{
	int retval;

#ifdef SUPPORT_IOCTL
	PUCHAR ke_area;
	int err;
	DWORD dwRet;
	PHPT_IOCTL_PARAM piop;
#endif
	char *buffer = hptproc_buffer;
	if (length >= 6) {
		if (strncmp(buffer,"hpt ",4) == 0) {
			IAL_ADAPTER_T *pAdapter;
			retval = buffer[4]-'0';
			for (pAdapter=gIal_Adapter; pAdapter; pAdapter=pAdapter->next) {
				if (pAdapter->mvSataAdapter.adapterId==retval)
					return (retval = hpt_set_asc_info(pAdapter, buffer+6, length-6)) >= 0? retval : -EINVAL;
			}
			return -EINVAL;
		}
#ifdef SUPPORT_IOCTL	
		piop = (PHPT_IOCTL_PARAM)buffer;
		if (piop->Magic == HPT_IOCTL_MAGIC || 
			piop->Magic == HPT_IOCTL_MAGIC32) 	{
			KdPrintE(("ioctl=%d in=%p len=%d out=%p len=%d\n", 
				piop->dwIoControlCode,
        			piop->lpInBuffer,
        			piop->nInBufferSize,
        			piop->lpOutBuffer,
	        		piop->nOutBufferSize));

			/*
        	 	 * map buffer to kernel.
        	 	 */
        		if (piop->nInBufferSize > PAGE_SIZE ||
        			piop->nOutBufferSize > PAGE_SIZE ||
        			piop->nInBufferSize+piop->nOutBufferSize > PAGE_SIZE) {
        			KdPrintE(("User buffer too large\n"));
        			return -EINVAL;
        		}
        		
        		ke_area = malloc(piop->nInBufferSize+piop->nOutBufferSize, M_DEVBUF, M_NOWAIT);
				if (ke_area == NULL) {
					KdPrintE(("Couldn't allocate kernel mem.\n"));
					return -EINVAL;
				}

			if (piop->nInBufferSize) {
				if (copyin((void*)(ULONG_PTR)piop->lpInBuffer, ke_area, piop->nInBufferSize) != 0) {
					KdPrintE(("Failed to copyin from lpInBuffer\n"));
					free(ke_area, M_DEVBUF);
					return -EFAULT;
				}
			}

			/*
			  * call kernel handler.
			  */    
			err = Kernel_DeviceIoControl(&gIal_Adapter->VBus,
				piop->dwIoControlCode, ke_area, piop->nInBufferSize,
				ke_area + piop->nInBufferSize, piop->nOutBufferSize, &dwRet);    
			
			if (err==0) {
				if (piop->nOutBufferSize)
					copyout(ke_area + piop->nInBufferSize, (void*)(ULONG_PTR)piop->lpOutBuffer, piop->nOutBufferSize);
				
				if (piop->lpBytesReturned)
					copyout(&dwRet, (void*)(ULONG_PTR)piop->lpBytesReturned, sizeof(DWORD));
			
				free(ke_area, M_DEVBUF);
				return length;
			}
			else  KdPrintW(("Kernel_ioctl(): return %d\n", err));

			free(ke_area, M_DEVBUF);
			return -EINVAL;
		} else 	{
    		KdPrintW(("Wrong signature: %x\n", piop->Magic));
    		return -EINVAL;
		}
#endif
	}

	return -EINVAL;
}