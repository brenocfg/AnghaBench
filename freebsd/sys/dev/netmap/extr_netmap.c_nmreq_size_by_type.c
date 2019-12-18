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
typedef  int uint16_t ;
struct nmreq_vale_polling {int dummy; } ;
struct nmreq_vale_newif {int dummy; } ;
struct nmreq_vale_list {int dummy; } ;
struct nmreq_vale_detach {int dummy; } ;
struct nmreq_vale_attach {int dummy; } ;
struct nmreq_sync_kloop_start {int dummy; } ;
struct nmreq_register {int dummy; } ;
struct nmreq_port_info_get {int dummy; } ;
struct nmreq_port_hdr {int dummy; } ;
struct nmreq_pools_info {int dummy; } ;

/* Variables and functions */
#define  NETMAP_REQ_CSB_ENABLE 142 
#define  NETMAP_REQ_POOLS_INFO_GET 141 
#define  NETMAP_REQ_PORT_HDR_GET 140 
#define  NETMAP_REQ_PORT_HDR_SET 139 
#define  NETMAP_REQ_PORT_INFO_GET 138 
#define  NETMAP_REQ_REGISTER 137 
#define  NETMAP_REQ_SYNC_KLOOP_START 136 
#define  NETMAP_REQ_SYNC_KLOOP_STOP 135 
#define  NETMAP_REQ_VALE_ATTACH 134 
#define  NETMAP_REQ_VALE_DELIF 133 
#define  NETMAP_REQ_VALE_DETACH 132 
#define  NETMAP_REQ_VALE_LIST 131 
#define  NETMAP_REQ_VALE_NEWIF 130 
#define  NETMAP_REQ_VALE_POLLING_DISABLE 129 
#define  NETMAP_REQ_VALE_POLLING_ENABLE 128 

size_t
nmreq_size_by_type(uint16_t nr_reqtype)
{
	switch (nr_reqtype) {
	case NETMAP_REQ_REGISTER:
		return sizeof(struct nmreq_register);
	case NETMAP_REQ_PORT_INFO_GET:
		return sizeof(struct nmreq_port_info_get);
	case NETMAP_REQ_VALE_ATTACH:
		return sizeof(struct nmreq_vale_attach);
	case NETMAP_REQ_VALE_DETACH:
		return sizeof(struct nmreq_vale_detach);
	case NETMAP_REQ_VALE_LIST:
		return sizeof(struct nmreq_vale_list);
	case NETMAP_REQ_PORT_HDR_SET:
	case NETMAP_REQ_PORT_HDR_GET:
		return sizeof(struct nmreq_port_hdr);
	case NETMAP_REQ_VALE_NEWIF:
		return sizeof(struct nmreq_vale_newif);
	case NETMAP_REQ_VALE_DELIF:
	case NETMAP_REQ_SYNC_KLOOP_STOP:
	case NETMAP_REQ_CSB_ENABLE:
		return 0;
	case NETMAP_REQ_VALE_POLLING_ENABLE:
	case NETMAP_REQ_VALE_POLLING_DISABLE:
		return sizeof(struct nmreq_vale_polling);
	case NETMAP_REQ_POOLS_INFO_GET:
		return sizeof(struct nmreq_pools_info);
	case NETMAP_REQ_SYNC_KLOOP_START:
		return sizeof(struct nmreq_sync_kloop_start);
	}
	return 0;
}