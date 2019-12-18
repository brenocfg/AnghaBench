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
typedef  scalar_t__ uint32_t ;
struct qlnx_fastpath {int /*<<< orphan*/  tx_lso_wnd_min_len; } ;
struct TYPE_3__ {scalar_t__ ds_len; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int ETH_TX_LSO_WINDOW_BDS_NUM ; 
 scalar_t__ ETH_TX_LSO_WINDOW_MIN_LEN ; 

__attribute__((used)) static __inline int
qlnx_tso_check(struct qlnx_fastpath *fp, bus_dma_segment_t *segs, int nsegs,
	uint32_t offset)
{
	int			i;
	uint32_t		sum, nbds_in_hdr = 1;
        uint32_t		window;
        bus_dma_segment_t	*s_seg;

        /* If the header spans mulitple segments, skip those segments */

        if (nsegs < ETH_TX_LSO_WINDOW_BDS_NUM)
                return (0);

        i = 0;

        while ((i < nsegs) && (offset >= segs->ds_len)) {
                offset = offset - segs->ds_len;
                segs++;
                i++;
                nbds_in_hdr++;
        }

        window = ETH_TX_LSO_WINDOW_BDS_NUM - nbds_in_hdr;

        nsegs = nsegs - i;

        while (nsegs >= window) {

                sum = 0;
                s_seg = segs;

                for (i = 0; i < window; i++){
                        sum += s_seg->ds_len;
                        s_seg++;
                }

                if (sum < ETH_TX_LSO_WINDOW_MIN_LEN) {
                        fp->tx_lso_wnd_min_len++;
                        return (-1);
                }

                nsegs = nsegs - 1;
                segs++;
        }

	return (0);
}