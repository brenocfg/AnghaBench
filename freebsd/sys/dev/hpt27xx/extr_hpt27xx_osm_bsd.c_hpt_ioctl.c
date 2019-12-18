#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  ioctl_args ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int nInBufferSize; int nOutBufferSize; int /*<<< orphan*/ * lpOutBuffer; int /*<<< orphan*/ * lpInBuffer; int /*<<< orphan*/  result; int /*<<< orphan*/ * lpBytesReturned; int /*<<< orphan*/  dwIoControlCode; } ;
struct TYPE_5__ {int nInBufferSize; int nOutBufferSize; scalar_t__ lpBytesReturned; scalar_t__ lpOutBuffer; scalar_t__ lpInBuffer; int /*<<< orphan*/  dwIoControlCode; int /*<<< orphan*/  Magic; } ;
typedef  TYPE_1__* PHPT_IOCTL_PARAM ;
typedef  TYPE_2__ IOCTL_ARG ;
typedef  int /*<<< orphan*/  HPT_U32 ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  Giant ; 
#define  HPT_DO_IOCONTROL 129 
 int /*<<< orphan*/  HPT_IOCTL_MAGIC ; 
 int /*<<< orphan*/  HPT_IOCTL_MAGIC32 ; 
 int /*<<< orphan*/  HPT_IOCTL_RESULT_OK ; 
#define  HPT_SCAN_BUS 128 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  copyin (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpt_do_ioctl (TYPE_2__*) ; 
 int hpt_rescan_bus () ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hpt_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag, struct thread *td)
{
	PHPT_IOCTL_PARAM piop=(PHPT_IOCTL_PARAM)data;
	IOCTL_ARG ioctl_args;
	HPT_U32 bytesReturned = 0;

	switch (cmd){
	case HPT_DO_IOCONTROL:
	{	
		if (piop->Magic == HPT_IOCTL_MAGIC || piop->Magic == HPT_IOCTL_MAGIC32) {
			KdPrint(("<8>ioctl=%x in=%p len=%d out=%p len=%d\n",
				piop->dwIoControlCode,
				piop->lpInBuffer,
				piop->nInBufferSize,
				piop->lpOutBuffer,
				piop->nOutBufferSize));
			
		memset(&ioctl_args, 0, sizeof(ioctl_args));
		
		ioctl_args.dwIoControlCode = piop->dwIoControlCode;
		ioctl_args.nInBufferSize = piop->nInBufferSize;
		ioctl_args.nOutBufferSize = piop->nOutBufferSize;
		ioctl_args.lpBytesReturned = &bytesReturned;

		if (ioctl_args.nInBufferSize) {
			ioctl_args.lpInBuffer = malloc(ioctl_args.nInBufferSize, M_DEVBUF, M_WAITOK);
			if (!ioctl_args.lpInBuffer)
				goto invalid;
			if (copyin((void*)piop->lpInBuffer,
					ioctl_args.lpInBuffer, piop->nInBufferSize))
				goto invalid;
		}
	
		if (ioctl_args.nOutBufferSize) {
			ioctl_args.lpOutBuffer = malloc(ioctl_args.nOutBufferSize, M_DEVBUF, M_WAITOK | M_ZERO);
			if (!ioctl_args.lpOutBuffer)
				goto invalid;
		}
		
#if __FreeBSD_version < 1000510
		mtx_lock(&Giant);
#endif

		hpt_do_ioctl(&ioctl_args);
	
#if __FreeBSD_version < 1000510
		mtx_unlock(&Giant);
#endif

		if (ioctl_args.result==HPT_IOCTL_RESULT_OK) {
			if (piop->nOutBufferSize) {
				if (copyout(ioctl_args.lpOutBuffer,
					(void*)piop->lpOutBuffer, piop->nOutBufferSize))
					goto invalid;
			}
			if (piop->lpBytesReturned) {
				if (copyout(&bytesReturned,
					(void*)piop->lpBytesReturned, sizeof(HPT_U32)))
					goto invalid;
			}
			if (ioctl_args.lpInBuffer) free(ioctl_args.lpInBuffer, M_DEVBUF);
			if (ioctl_args.lpOutBuffer) free(ioctl_args.lpOutBuffer, M_DEVBUF);
			return 0;
		}
invalid:
		if (ioctl_args.lpInBuffer) free(ioctl_args.lpInBuffer, M_DEVBUF);
		if (ioctl_args.lpOutBuffer) free(ioctl_args.lpOutBuffer, M_DEVBUF);
		return EFAULT;
	}
	return EFAULT;
	}

	case HPT_SCAN_BUS:
	{
		return hpt_rescan_bus();
	}
	default:
		KdPrint(("invalid command!"));
		return EFAULT;
	}	

}