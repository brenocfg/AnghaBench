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
typedef  int u_int ;
typedef  int u_char ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int EXTRACT_24BITS (int const*) ; 
 int EXTRACT_32BITS (int const*) ; 
 int EXTRACT_LE_16BITS (int const*) ; 
 int EXTRACT_LE_24BITS (int const*) ; 
 int EXTRACT_LE_32BITS (int const*) ; 

__attribute__((used)) static int
juniper_read_tlv_value(const u_char *p, u_int tlv_type, u_int tlv_len)
{
   int tlv_value;

   /* TLVs < 128 are little endian encoded */
   if (tlv_type < 128) {
       switch (tlv_len) {
       case 1:
           tlv_value = *p;
           break;
       case 2:
           tlv_value = EXTRACT_LE_16BITS(p);
           break;
       case 3:
           tlv_value = EXTRACT_LE_24BITS(p);
           break;
       case 4:
           tlv_value = EXTRACT_LE_32BITS(p);
           break;
       default:
           tlv_value = -1;
           break;
       }
   } else {
       /* TLVs >= 128 are big endian encoded */
       switch (tlv_len) {
       case 1:
           tlv_value = *p;
           break;
       case 2:
           tlv_value = EXTRACT_16BITS(p);
           break;
       case 3:
           tlv_value = EXTRACT_24BITS(p);
           break;
       case 4:
           tlv_value = EXTRACT_32BITS(p);
           break;
       default:
           tlv_value = -1;
           break;
       }
   }
   return tlv_value;
}