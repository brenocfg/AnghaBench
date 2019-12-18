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
typedef  int uint8_t ;

/* Variables and functions */
 int TH_ACK ; 
 int TH_FIN ; 
 int TH_RST ; 
 int TH_SYN ; 

__attribute__((used)) static inline uint8_t
convert_tcp_flags(uint8_t flags)
{
	uint8_t result;

	result = flags & (TH_FIN|TH_SYN);
	result |= (flags & TH_RST) >> 2; /* Treat RST as FIN */
	result |= (flags & TH_ACK) >> 2; /* Treat ACK as estab */

	return (result);
}