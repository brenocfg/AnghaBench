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
typedef  char u_char ;
struct mbuf {int m_len; struct mbuf* m_next; } ;

/* Variables and functions */
 char* CONST_MBUF_CTOP (struct mbuf const*) ; 
 scalar_t__ isprint (char const) ; 
 scalar_t__ log_IsKept (int) ; 
 int /*<<< orphan*/  log_Printf (int,char*,char const*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
log_DumpBp(int lev, const char *hdr, const struct mbuf *bp)
{
  if (log_IsKept(lev)) {
    char buf[68];
    char *b, *c;
    const u_char *ptr;
    int f;

    if (hdr && *hdr)
      log_Printf(lev, "%s\n", hdr);

    b = buf;
    c = b + 50;
    do {
      f = bp->m_len;
      ptr = CONST_MBUF_CTOP(bp);
      while (f--) {
	sprintf(b, " %02x", (int) *ptr);
        *c++ = isprint(*ptr) ? *ptr : '.';
        ptr++;
        b += 3;
        if (b == buf + 48) {
          memset(b, ' ', 2);
          *c = '\0';
          log_Printf(lev, "%s\n", buf);
          b = buf;
          c = b + 50;
        }
      }
    } while ((bp = bp->m_next) != NULL);

    if (b > buf) {
      memset(b, ' ', 50 - (b - buf));
      *c = '\0';
      log_Printf(lev, "%s\n", buf);
    }
  }
}