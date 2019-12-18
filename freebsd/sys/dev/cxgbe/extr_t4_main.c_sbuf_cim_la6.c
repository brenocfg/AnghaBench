#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct sbuf {int dummy; } ;
struct TYPE_2__ {int cim_la_size; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int F_UPDBGLACAPTPCONLY ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static void
sbuf_cim_la6(struct adapter *sc, struct sbuf *sb, uint32_t *buf, uint32_t cfg)
{
	uint32_t *p;

	sbuf_printf(sb, "Status   Inst    Data      PC%s",
	    cfg & F_UPDBGLACAPTPCONLY ? "" :
	    "     LS0Stat  LS0Addr  LS0Data  LS1Stat  LS1Addr  LS1Data");

	for (p = buf; p <= &buf[sc->params.cim_la_size - 10]; p += 10) {
		if (cfg & F_UPDBGLACAPTPCONLY) {
			sbuf_printf(sb, "\n  %02x   %08x %08x %08x",
			    p[3] & 0xff, p[2], p[1], p[0]);
			sbuf_printf(sb, "\n  %02x   %02x%06x %02x%06x %02x%06x",
			    (p[6] >> 8) & 0xff, p[6] & 0xff, p[5] >> 8,
			    p[5] & 0xff, p[4] >> 8, p[4] & 0xff, p[3] >> 8);
			sbuf_printf(sb, "\n  %02x   %04x%04x %04x%04x %04x%04x",
			    (p[9] >> 16) & 0xff, p[9] & 0xffff, p[8] >> 16,
			    p[8] & 0xffff, p[7] >> 16, p[7] & 0xffff,
			    p[6] >> 16);
		} else {
			sbuf_printf(sb, "\n  %02x   %04x%04x %04x%04x %04x%04x "
			    "%08x %08x %08x %08x %08x %08x",
			    (p[9] >> 16) & 0xff,
			    p[9] & 0xffff, p[8] >> 16,
			    p[8] & 0xffff, p[7] >> 16,
			    p[7] & 0xffff, p[6] >> 16,
			    p[2], p[1], p[0], p[5], p[4], p[3]);
		}
	}
}