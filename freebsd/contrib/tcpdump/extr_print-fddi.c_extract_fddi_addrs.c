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
struct fddi_header {size_t* fddi_dhost; size_t* fddi_shost; } ;

/* Variables and functions */
 char* fddi_bit_swap ; 
 scalar_t__ fddi_bitswap ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static inline void
extract_fddi_addrs(const struct fddi_header *fddip, char *fsrc, char *fdst)
{
	register int i;

	if (fddi_bitswap) {
		/*
		 * bit-swap the fddi addresses (isn't the IEEE standards
		 * process wonderful!) then convert them to names.
		 */
		for (i = 0; i < 6; ++i)
			fdst[i] = fddi_bit_swap[fddip->fddi_dhost[i]];
		for (i = 0; i < 6; ++i)
			fsrc[i] = fddi_bit_swap[fddip->fddi_shost[i]];
	}
	else {
		memcpy(fdst, (const char *)fddip->fddi_dhost, 6);
		memcpy(fsrc, (const char *)fddip->fddi_shost, 6);
	}
}