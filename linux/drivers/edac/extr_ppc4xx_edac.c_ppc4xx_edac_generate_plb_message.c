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
struct ppc4xx_ecc_status {int besr; } ;
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 int SDRAM_BESR_M0ET_MASK ; 
 int SDRAM_BESR_M0ET_NONE ; 
 unsigned int SDRAM_BESR_M0ID_DECODE (int) ; 
 int SDRAM_BESR_M0RW_MASK ; 
 int SDRAM_BESR_M0RW_READ ; 
 int SDRAM_BESR_MASK ; 
 unsigned int SDRAM_PLB_M0ID_FIRST ; 
 unsigned int SDRAM_PLB_M0ID_LAST ; 
 char** ppc4xx_plb_masters ; 
 int snprintf (char*,size_t,char*,char*,unsigned int,char*) ; 

__attribute__((used)) static int
ppc4xx_edac_generate_plb_message(const struct mem_ctl_info *mci,
				 const struct ppc4xx_ecc_status *status,
				 char *buffer,
				 size_t size)
{
	unsigned int master;
	bool read;

	if ((status->besr & SDRAM_BESR_MASK) == 0)
		return 0;

	if ((status->besr & SDRAM_BESR_M0ET_MASK) == SDRAM_BESR_M0ET_NONE)
		return 0;

	read = ((status->besr & SDRAM_BESR_M0RW_MASK) == SDRAM_BESR_M0RW_READ);

	master = SDRAM_BESR_M0ID_DECODE(status->besr);

	return snprintf(buffer, size,
			"%s error w/ PLB master %u \"%s\"; ",
			(read ? "Read" : "Write"),
			master,
			(((master >= SDRAM_PLB_M0ID_FIRST) &&
			  (master <= SDRAM_PLB_M0ID_LAST)) ?
			 ppc4xx_plb_masters[master] : "UNKNOWN"));
}