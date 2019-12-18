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
typedef  size_t u_int ;
typedef  struct fsmheader {size_t code; size_t id; int /*<<< orphan*/  length; } const fsmheader ;
typedef  struct fsmheader u_char ;
struct physical {int /*<<< orphan*/  link; TYPE_1__* dl; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bundle; } ;

/* Variables and functions */
 scalar_t__ LINK_QUEUES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  LogPHASE ; 
 scalar_t__ MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_CHAPOUT ; 
 int /*<<< orphan*/  PROTO_CHAP ; 
 int /*<<< orphan*/ * chapcodes ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  link_PushPacket (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_DumpBp (int /*<<< orphan*/ ,char*,struct mbuf*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 struct mbuf* m_get (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct fsmheader const*,int) ; 

__attribute__((used)) static void
ChapOutput(struct physical *physical, u_int code, u_int id,
	   const u_char *ptr, int count, const char *text)
{
  int plen;
  struct fsmheader lh;
  struct mbuf *bp;

  plen = sizeof(struct fsmheader) + count;
  lh.code = code;
  lh.id = id;
  lh.length = htons(plen);
  bp = m_get(plen, MB_CHAPOUT);
  memcpy(MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  if (count)
    memcpy(MBUF_CTOP(bp) + sizeof(struct fsmheader), ptr, count);
  log_DumpBp(LogDEBUG, "ChapOutput", bp);
  if (text == NULL)
    log_Printf(LogPHASE, "Chap Output: %s\n", chapcodes[code]);
  else
    log_Printf(LogPHASE, "Chap Output: %s (%s)\n", chapcodes[code], text);
  link_PushPacket(&physical->link, bp, physical->dl->bundle,
                  LINK_QUEUES(&physical->link) - 1, PROTO_CHAP);
}