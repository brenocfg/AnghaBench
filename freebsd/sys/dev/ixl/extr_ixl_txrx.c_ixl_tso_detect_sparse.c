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
typedef  TYPE_1__* if_pkt_info_t ;
struct TYPE_6__ {int ds_len; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_5__ {int ipi_tso_segsz; int ipi_ehdrlen; int ipi_ip_hlen; int ipi_tcp_hlen; int ipi_len; } ;

/* Variables and functions */
 int IXL_MAX_TX_SEGS ; 
 scalar_t__ __predict_false (int) ; 
 int min (int,int) ; 

__attribute__((used)) static int
ixl_tso_detect_sparse(bus_dma_segment_t *segs, int nsegs, if_pkt_info_t pi)
{
	int	count, curseg, i, hlen, segsz, seglen, tsolen;

	if (nsegs <= IXL_MAX_TX_SEGS-2)
		return (0);
	segsz = pi->ipi_tso_segsz;
	curseg = count = 0;

	hlen = pi->ipi_ehdrlen + pi->ipi_ip_hlen + pi->ipi_tcp_hlen;
	tsolen = pi->ipi_len - hlen;

	i = 0;
	curseg = segs[0].ds_len;
	while (hlen > 0) {
		count++;
		if (count > IXL_MAX_TX_SEGS - 2)
			return (1);
		if (curseg == 0) {
			i++;
			if (__predict_false(i == nsegs))
				return (1);

			curseg = segs[i].ds_len;
		}
		seglen = min(curseg, hlen);
		curseg -= seglen;
		hlen -= seglen;
		// printf("H:seglen = %d, count=%d\n", seglen, count);
	}
	while (tsolen > 0) {
		segsz = pi->ipi_tso_segsz;
		while (segsz > 0 && tsolen != 0) {
			count++;
			if (count > IXL_MAX_TX_SEGS - 2) {
				// printf("bad: count = %d\n", count);
				return (1);
			}
			if (curseg == 0) {
				i++;
				if (__predict_false(i == nsegs)) {
					// printf("bad: tsolen = %d", tsolen);
					return (1);
				}
				curseg = segs[i].ds_len;
			}
			seglen = min(curseg, segsz);
			segsz -= seglen;
			curseg -= seglen;
			tsolen -= seglen;
			// printf("D:seglen = %d, count=%d\n", seglen, count);
		}
		count = 0;
	}

 	return (0);
}