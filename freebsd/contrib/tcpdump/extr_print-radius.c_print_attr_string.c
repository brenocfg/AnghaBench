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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  EGRESS_VLAN_NAME 135 
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
#define  TUNNEL_ASSIGN_ID 134 
#define  TUNNEL_CLIENT_AUTH 133 
#define  TUNNEL_CLIENT_END 132 
#define  TUNNEL_PASS 131 
#define  TUNNEL_PRIV_GROUP 130 
#define  TUNNEL_SERVER_AUTH 129 
#define  TUNNEL_SERVER_END 128 
 int /*<<< orphan*/  rfc4675_tagged ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
print_attr_string(netdissect_options *ndo,
                  register const u_char *data, u_int length, u_short attr_code)
{
   register u_int i;

   ND_TCHECK2(data[0],length);

   switch(attr_code)
   {
      case TUNNEL_PASS:
           if (length < 3)
              goto trunc;
           if (*data && (*data <=0x1F) )
              ND_PRINT((ndo, "Tag[%u] ", *data));
           else
              ND_PRINT((ndo, "Tag[Unused] "));
           data++;
           length--;
           ND_PRINT((ndo, "Salt %u ", EXTRACT_16BITS(data)));
           data+=2;
           length-=2;
        break;
      case TUNNEL_CLIENT_END:
      case TUNNEL_SERVER_END:
      case TUNNEL_PRIV_GROUP:
      case TUNNEL_ASSIGN_ID:
      case TUNNEL_CLIENT_AUTH:
      case TUNNEL_SERVER_AUTH:
           if (*data <= 0x1F)
           {
              if (length < 1)
                 goto trunc;
              if (*data)
                ND_PRINT((ndo, "Tag[%u] ", *data));
              else
                ND_PRINT((ndo, "Tag[Unused] "));
              data++;
              length--;
           }
        break;
      case EGRESS_VLAN_NAME:
           if (length < 1)
              goto trunc;
           ND_PRINT((ndo, "%s (0x%02x) ",
                  tok2str(rfc4675_tagged,"Unknown tag",*data),
                  *data));
           data++;
           length--;
        break;
   }

   for (i=0; i < length && *data; i++, data++)
       ND_PRINT((ndo, "%c", (*data < 32 || *data > 126) ? '.' : *data));

   return;

   trunc:
      ND_PRINT((ndo, "%s", tstr));
}