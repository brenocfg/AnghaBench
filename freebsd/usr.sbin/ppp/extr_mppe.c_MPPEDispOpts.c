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
struct fsm_opt {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int MPPE_OPT_128BIT ; 
 int MPPE_OPT_40BIT ; 
 int MPPE_OPT_56BIT ; 
 int MPPE_OPT_BITMASK ; 
 int MPPE_OPT_COMPRESSED ; 
 int MPPE_OPT_STATELESS ; 
 int snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  ua_ntohl (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static const char *
MPPEDispOpts(struct fsm_opt *o)
{
  static char buf[70];
  u_int32_t val;
  char ch;
  int len, n;

  ua_ntohl(o->data, &val);
  len = 0;
  if ((n = snprintf(buf, sizeof buf, "value 0x%08x ", (unsigned)val)) > 0)
    len += n;
  if (!(val & MPPE_OPT_BITMASK)) {
    if ((n = snprintf(buf + len, sizeof buf - len, "(0")) > 0)
      len += n;
  } else {
    ch = '(';
    if (val & MPPE_OPT_128BIT) {
      if ((n = snprintf(buf + len, sizeof buf - len, "%c128", ch)) > 0)
        len += n;
      ch = '/';
    }
    if (val & MPPE_OPT_56BIT) {
      if ((n = snprintf(buf + len, sizeof buf - len, "%c56", ch)) > 0)
        len += n;
      ch = '/';
    }
    if (val & MPPE_OPT_40BIT) {
      if ((n = snprintf(buf + len, sizeof buf - len, "%c40", ch)) > 0)
        len += n;
      ch = '/';
    }
  }

  if ((n = snprintf(buf + len, sizeof buf - len, " bits, state%s",
                    (val & MPPE_OPT_STATELESS) ? "less" : "ful")) > 0)
    len += n;

  if (val & MPPE_OPT_COMPRESSED) {
    if ((n = snprintf(buf + len, sizeof buf - len, ", compressed")) > 0)
      len += n;
  }

  snprintf(buf + len, sizeof buf - len, ")");

  return buf;
}