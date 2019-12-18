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
typedef  int u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
#define  FRM_IPADDR 129 
#define  LOG_IPHOST 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
print_attr_address(netdissect_options *ndo,
                   register const u_char *data, u_int length, u_short attr_code)
{
   if (length != 4)
   {
       ND_PRINT((ndo, "ERROR: length %u != 4", length));
       return;
   }

   ND_TCHECK2(data[0],4);

   switch(attr_code)
   {
      case FRM_IPADDR:
      case LOG_IPHOST:
           if (EXTRACT_32BITS(data) == 0xFFFFFFFF )
              ND_PRINT((ndo, "User Selected"));
           else
              if (EXTRACT_32BITS(data) == 0xFFFFFFFE )
                 ND_PRINT((ndo, "NAS Select"));
              else
                 ND_PRINT((ndo, "%s",ipaddr_string(ndo, data)));
      break;

      default:
          ND_PRINT((ndo, "%s", ipaddr_string(ndo, data)));
      break;
   }

   return;

   trunc:
     ND_PRINT((ndo, "%s", tstr));
}