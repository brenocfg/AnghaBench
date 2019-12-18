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

/* Variables and functions */
 int NC_TPI_CLTS ; 
 int NC_TPI_COTS_ORD ; 
 int NC_TPI_RAW ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_STREAM 128 

int
__rpc_socktype2seman(int socktype)
{
	switch (socktype) {
	case SOCK_DGRAM:
		return NC_TPI_CLTS;
	case SOCK_STREAM:
		return NC_TPI_COTS_ORD;
	case SOCK_RAW:
		return NC_TPI_RAW;
	default:
		break;
	}

	return -1;
}