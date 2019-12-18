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
struct remote_state {int /*<<< orphan*/  remote_packet_size; } ;
struct objfile {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct TYPE_3__ {scalar_t__ support; } ;

/* Variables and functions */
 scalar_t__ PACKET_DISABLE ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 char* alloca (int /*<<< orphan*/ ) ; 
 struct remote_state* get_remote_state () ; 
 int /*<<< orphan*/  getpkt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hex2bin (char*,char*,int) ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_ok (char*,TYPE_1__*) ; 
 char* paddr_nz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 TYPE_1__ remote_protocol_qSymbol ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
remote_check_symbols (struct objfile *objfile)
{
  struct remote_state *rs = get_remote_state ();
  char *msg, *reply, *tmp;
  struct minimal_symbol *sym;
  int end;

  if (remote_protocol_qSymbol.support == PACKET_DISABLE)
    return;

  msg   = alloca (rs->remote_packet_size);
  reply = alloca (rs->remote_packet_size);

  /* Invite target to request symbol lookups. */

  putpkt ("qSymbol::");
  getpkt (reply, (rs->remote_packet_size), 0);
  packet_ok (reply, &remote_protocol_qSymbol);

  while (strncmp (reply, "qSymbol:", 8) == 0)
    {
      tmp = &reply[8];
      end = hex2bin (tmp, msg, strlen (tmp) / 2);
      msg[end] = '\0';
      sym = lookup_minimal_symbol (msg, NULL, NULL);
      if (sym == NULL)
	sprintf (msg, "qSymbol::%s", &reply[8]);
      else
	sprintf (msg, "qSymbol:%s:%s",
		 paddr_nz (SYMBOL_VALUE_ADDRESS (sym)),
		 &reply[8]);
      putpkt (msg);
      getpkt (reply, (rs->remote_packet_size), 0);
    }
}