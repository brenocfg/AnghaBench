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
typedef  size_t uint64_t ;
typedef  int uint32_t ;
struct nmreq_option {int dummy; } ;
struct nmreq_opt_sync_kloop_mode {int dummy; } ;
struct nmreq_opt_extmem {int dummy; } ;
struct nmreq_opt_csb {int dummy; } ;

/* Variables and functions */
#define  NETMAP_REQ_OPT_CSB 131 
 int NETMAP_REQ_OPT_DEBUG ; 
#define  NETMAP_REQ_OPT_EXTMEM 130 
#define  NETMAP_REQ_OPT_SYNC_KLOOP_EVENTFDS 129 
#define  NETMAP_REQ_OPT_SYNC_KLOOP_MODE 128 

__attribute__((used)) static size_t
nmreq_opt_size_by_type(uint32_t nro_reqtype, uint64_t nro_size)
{
	size_t rv = sizeof(struct nmreq_option);
#ifdef NETMAP_REQ_OPT_DEBUG
	if (nro_reqtype & NETMAP_REQ_OPT_DEBUG)
		return (nro_reqtype & ~NETMAP_REQ_OPT_DEBUG);
#endif /* NETMAP_REQ_OPT_DEBUG */
	switch (nro_reqtype) {
#ifdef WITH_EXTMEM
	case NETMAP_REQ_OPT_EXTMEM:
		rv = sizeof(struct nmreq_opt_extmem);
		break;
#endif /* WITH_EXTMEM */
	case NETMAP_REQ_OPT_SYNC_KLOOP_EVENTFDS:
		if (nro_size >= rv)
			rv = nro_size;
		break;
	case NETMAP_REQ_OPT_CSB:
		rv = sizeof(struct nmreq_opt_csb);
		break;
	case NETMAP_REQ_OPT_SYNC_KLOOP_MODE:
		rv = sizeof(struct nmreq_opt_sync_kloop_mode);
		break;
	}
	/* subtract the common header */
	return rv - sizeof(struct nmreq_option);
}