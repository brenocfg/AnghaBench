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
typedef  int u_int16_t ;
struct mp_header {int begin; int end; int seq; } ;
struct mp {scalar_t__ local_is12bit; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ua_ntohl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ua_ntohs (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mp_ReadHeader(struct mp *mp, struct mbuf *m, struct mp_header *header)
{
  if (mp->local_is12bit) {
    u_int16_t val;

    ua_ntohs(MBUF_CTOP(m), &val);
    if (val & 0x3000) {
      log_Printf(LogWARN, "Oops - MP header without required zero bits\n");
      return 0;
    }
    header->begin = val & 0x8000 ? 1 : 0;
    header->end = val & 0x4000 ? 1 : 0;
    header->seq = val & 0x0fff;
    return 2;
  } else {
    ua_ntohl(MBUF_CTOP(m), &header->seq);
    if (header->seq & 0x3f000000) {
      log_Printf(LogWARN, "Oops - MP header without required zero bits\n");
      return 0;
    }
    header->begin = header->seq & 0x80000000 ? 1 : 0;
    header->end = header->seq & 0x40000000 ? 1 : 0;
    header->seq &= 0x00ffffff;
    return 4;
  }
}