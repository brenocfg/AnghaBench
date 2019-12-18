#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct radius_hdr {int /*<<< orphan*/ * auth; int /*<<< orphan*/  id; int /*<<< orphan*/  code; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ MIN_RADIUS_LEN ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  radius_attrs_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  radius_command_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

void
radius_print(netdissect_options *ndo,
             const u_char *dat, u_int length)
{
   register const struct radius_hdr *rad;
   u_int len, auth_idx;

   ND_TCHECK2(*dat, MIN_RADIUS_LEN);
   rad = (const struct radius_hdr *)dat;
   len = EXTRACT_16BITS(&rad->len);

   if (len < MIN_RADIUS_LEN)
   {
	  ND_PRINT((ndo, "%s", tstr));
	  return;
   }

   if (len > length)
	  len = length;

   if (ndo->ndo_vflag < 1) {
       ND_PRINT((ndo, "RADIUS, %s (%u), id: 0x%02x length: %u",
              tok2str(radius_command_values,"Unknown Command",rad->code),
              rad->code,
              rad->id,
              len));
       return;
   }
   else {
       ND_PRINT((ndo, "RADIUS, length: %u\n\t%s (%u), id: 0x%02x, Authenticator: ",
              len,
              tok2str(radius_command_values,"Unknown Command",rad->code),
              rad->code,
              rad->id));

       for(auth_idx=0; auth_idx < 16; auth_idx++)
            ND_PRINT((ndo, "%02x", rad->auth[auth_idx]));
   }

   if (len > MIN_RADIUS_LEN)
      radius_attrs_print(ndo, dat + MIN_RADIUS_LEN, len - MIN_RADIUS_LEN);
   return;

trunc:
   ND_PRINT((ndo, "%s", tstr));
}