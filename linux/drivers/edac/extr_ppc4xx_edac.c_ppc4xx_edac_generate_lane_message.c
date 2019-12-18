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
struct ppc4xx_ecc_status {int ecces; } ;
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 int SDRAM_ECCES_BNCE_ENCODE (unsigned int) ; 
 int snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int
ppc4xx_edac_generate_lane_message(const struct mem_ctl_info *mci,
				  const struct ppc4xx_ecc_status *status,
				  char *buffer,
				  size_t size)
{
	int n, total = 0;
	unsigned int lane, lanes;
	const unsigned int first_lane = 0;
	const unsigned int lane_count = 16;

	n = snprintf(buffer, size, "; Byte Lane Errors: ");

	if (n < 0 || n >= size)
		goto fail;

	buffer += n;
	size -= n;
	total += n;

	for (lanes = 0, lane = first_lane; lane < lane_count; lane++) {
		if ((status->ecces & SDRAM_ECCES_BNCE_ENCODE(lane)) != 0) {
			n = snprintf(buffer, size,
				     "%s%u",
				     (lanes++ ? ", " : ""), lane);

			if (n < 0 || n >= size)
				goto fail;

			buffer += n;
			size -= n;
			total += n;
		}
	}

	n = snprintf(buffer, size, "%s; ", lanes ? "" : "None");

	if (n < 0 || n >= size)
		goto fail;

	buffer += n;
	size -= n;
	total += n;

 fail:
	return total;
}