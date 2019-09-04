#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int blksize; int timeout; int tsize; char* options; } ;
struct TYPE_6__ {TYPE_1__ rrq; } ;
struct TYPE_7__ {char* error_msg; TYPE_2__ u; int /*<<< orphan*/  error_code; } ;
typedef  TYPE_3__ tftp_packet_t ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int tftp_fetch_string (char*,int) ; 
 int /*<<< orphan*/  tftp_option_negotiation ; 

int tftp_parse_options (tftp_packet_t *p, char *in, int avail_in) {
  p->u.rrq.blksize = p->u.rrq.timeout = 0;
  p->u.rrq.tsize = -1;
  if (!avail_in) {
    p->u.rrq.options = "";
    return 0;
  }
  p->u.rrq.options = in;
  while (avail_in > 0) {
    if (p->u.rrq.options != in) {
      in[-1] = ',';
    }
    int i;
    char *z[2];
    for (i = 0; i < 2; i++) {
      const int l = tftp_fetch_string (in, avail_in);
      if (l < 0) {
        p->error_code = tftp_option_negotiation;
        p->error_msg = "Format error: option isn't NUL-terminated.";
        return -1;
      }
      z[i] = in;
      in += l;
      avail_in -= l;
    }
    if (!strcmp (z[0], "blksize")) {
      i = atoi (z[1]);
      if (i >= 8 && i <= 65464) {
        p->u.rrq.blksize = i;
      }
    }
    if (!strcmp (z[0], "timeout")) {
      i = atoi (z[1]);
      if (i >= 1 && i <= 255) {
        p->u.rrq.timeout = i;
      }
    }
    if (!strcmp (z[0], "tsize")) {
      i = atoi (z[1]);
      if (i >= 0) {
        p->u.rrq.tsize = i;
      }
    }
    z[1][-1] = '=';
  }
  return 0;
}