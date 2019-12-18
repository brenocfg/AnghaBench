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
#define  ARAP_CHALLENGE_RESP 130 
#define  ARAP_FEATURES 129 
#define  ARAP_PASS 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  PRINT_HEX (int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
print_attr_strange(netdissect_options *ndo,
                   register const u_char *data, u_int length, u_short attr_code)
{
   u_short len_data;

   switch(attr_code)
   {
      case ARAP_PASS:
           if (length != 16)
           {
               ND_PRINT((ndo, "ERROR: length %u != 16", length));
               return;
           }
           ND_PRINT((ndo, "User_challenge ("));
           ND_TCHECK2(data[0],8);
           len_data = 8;
           PRINT_HEX(len_data, data);
           ND_PRINT((ndo, ") User_resp("));
           ND_TCHECK2(data[0],8);
           len_data = 8;
           PRINT_HEX(len_data, data);
           ND_PRINT((ndo, ")"));
        break;

      case ARAP_FEATURES:
           if (length != 14)
           {
               ND_PRINT((ndo, "ERROR: length %u != 14", length));
               return;
           }
           ND_TCHECK2(data[0],1);
           if (*data)
              ND_PRINT((ndo, "User can change password"));
           else
              ND_PRINT((ndo, "User cannot change password"));
           data++;
           ND_TCHECK2(data[0],1);
           ND_PRINT((ndo, ", Min password length: %d", *data));
           data++;
           ND_PRINT((ndo, ", created at: "));
           ND_TCHECK2(data[0],4);
           len_data = 4;
           PRINT_HEX(len_data, data);
           ND_PRINT((ndo, ", expires in: "));
           ND_TCHECK2(data[0],4);
           len_data = 4;
           PRINT_HEX(len_data, data);
           ND_PRINT((ndo, ", Current Time: "));
           ND_TCHECK2(data[0],4);
           len_data = 4;
           PRINT_HEX(len_data, data);
        break;

      case ARAP_CHALLENGE_RESP:
           if (length < 8)
           {
               ND_PRINT((ndo, "ERROR: length %u != 8", length));
               return;
           }
           ND_TCHECK2(data[0],8);
           len_data = 8;
           PRINT_HEX(len_data, data);
        break;
   }
   return;

   trunc:
     ND_PRINT((ndo, "%s", tstr));
}