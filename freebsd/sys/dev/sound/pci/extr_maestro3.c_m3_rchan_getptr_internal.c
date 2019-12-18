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
typedef  int u_int32_t ;
struct sc_rchinfo {int /*<<< orphan*/  adc_idx; scalar_t__ adc_data; int /*<<< orphan*/  buffer; struct sc_info* parent; } ;
struct sc_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALL ; 
 scalar_t__ CDATA_HOST_SRC_CURRENTH ; 
 scalar_t__ CDATA_HOST_SRC_CURRENTL ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int m3_rd_assp_data (struct sc_info*,scalar_t__) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
m3_rchan_getptr_internal(struct sc_rchinfo *ch)
{
	struct sc_info *sc = ch->parent;
	u_int32_t hi, lo, bus_base, bus_crnt;

	bus_base = sndbuf_getbufaddr(ch->buffer);
	hi = m3_rd_assp_data(sc, ch->adc_data + CDATA_HOST_SRC_CURRENTH);
        lo = m3_rd_assp_data(sc, ch->adc_data + CDATA_HOST_SRC_CURRENTL);
        bus_crnt = lo | (hi << 16);

	M3_DEBUG(CALL, ("m3_rchan_getptr(adc=%d) result=%d\n",
			ch->adc_idx, bus_crnt - bus_base));

	return (bus_crnt - bus_base); /* current byte offset of channel */
}