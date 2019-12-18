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
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_ok (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 int /*<<< orphan*/  remote_protocol_vcont ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
remote_vcont_probe (struct remote_state *rs, char *buf)
{
  strcpy (buf, "vCont?");
  putpkt (buf);
  getpkt (buf, rs->remote_packet_size, 0);

  /* Make sure that the features we assume are supported.  */
  if (strncmp (buf, "vCont", 5) == 0)
    {
      char *p = &buf[5];
      int support_s, support_S, support_c, support_C;

      support_s = 0;
      support_S = 0;
      support_c = 0;
      support_C = 0;
      while (p && *p == ';')
	{
	  p++;
	  if (*p == 's' && (*(p + 1) == ';' || *(p + 1) == 0))
	    support_s = 1;
	  else if (*p == 'S' && (*(p + 1) == ';' || *(p + 1) == 0))
	    support_S = 1;
	  else if (*p == 'c' && (*(p + 1) == ';' || *(p + 1) == 0))
	    support_c = 1;
	  else if (*p == 'C' && (*(p + 1) == ';' || *(p + 1) == 0))
	    support_C = 1;

	  p = strchr (p, ';');
	}

      /* If s, S, c, and C are not all supported, we can't use vCont.  Clearing
         BUF will make packet_ok disable the packet.  */
      if (!support_s || !support_S || !support_c || !support_C)
	buf[0] = 0;
    }

  packet_ok (buf, &remote_protocol_vcont);
}