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
typedef  int u_char ;
struct mbuf {int dummy; } ;
struct async {int mode; int* hbuff; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDLCSIZE ; 
#define  HDLC_ESC 129 
#define  HDLC_SYN 128 
 int HDLC_XOR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MB_ASYNCIN ; 
 int MODE_ESC ; 
 int MODE_HUNT ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_Write (struct mbuf*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
async_Decode(struct async *async, u_char c)
{
  struct mbuf *bp;

  if ((async->mode & MODE_HUNT) && c != HDLC_SYN)
    return NULL;

  switch (c) {
  case HDLC_SYN:
    async->mode &= ~MODE_HUNT;
    if (async->length) {		/* packet is ready. */
      bp = m_get(async->length, MB_ASYNCIN);
      mbuf_Write(bp, async->hbuff, async->length);
      async->length = 0;
      return bp;
    }
    break;
  case HDLC_ESC:
    if (!(async->mode & MODE_ESC)) {
      async->mode |= MODE_ESC;
      break;
    }
    /* FALLTHROUGH */
  default:
    if (async->length >= HDLCSIZE) {
      /* packet is too large, discard it */
      log_Printf(LogWARN, "Packet too large (%d), discarding.\n",
                 async->length);
      async->length = 0;
      async->mode = MODE_HUNT;
      break;
    }
    if (async->mode & MODE_ESC) {
      c ^= HDLC_XOR;
      async->mode &= ~MODE_ESC;
    }
    async->hbuff[async->length++] = c;
    break;
  }
  return NULL;
}