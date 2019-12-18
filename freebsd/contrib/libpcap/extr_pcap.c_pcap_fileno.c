#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; scalar_t__ handle; } ;
typedef  TYPE_1__ pcap_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int PCAP_ERROR ; 

int
pcap_fileno(pcap_t *p)
{
#ifndef _WIN32
	return (p->fd);
#else
	if (p->handle != INVALID_HANDLE_VALUE)
		return ((int)(DWORD)p->handle);
	else
		return (PCAP_ERROR);
#endif
}