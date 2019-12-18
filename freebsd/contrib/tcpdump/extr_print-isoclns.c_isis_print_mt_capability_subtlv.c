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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/ * tptr ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int EXTRACT_24BITS (int const*) ; 
 int EXTRACT_32BITS (int const*) ; 
#define  ISIS_SUBTLV_SPBM_SI 129 
#define  ISIS_SUBTLV_SPB_INSTANCE 128 
 int ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN ; 
 int ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  isis_mt_capability_subtlv_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
isis_print_mt_capability_subtlv(netdissect_options *ndo,
                                const uint8_t *tptr, int len)
{
  int stlv_type, stlv_len, tmp;

  while (len > 2)
  {
    ND_TCHECK2(*tptr, 2);
    stlv_type = *(tptr++);
    stlv_len  = *(tptr++);

    /* first lets see if we know the subTLVs name*/
    ND_PRINT((ndo, "\n\t      %s subTLV #%u, length: %u",
               tok2str(isis_mt_capability_subtlv_values, "unknown", stlv_type),
               stlv_type,
               stlv_len));

    len = len - 2;

    /* Make sure the subTLV fits within the space left */
    if (len < stlv_len)
      goto trunc;
    /* Make sure the entire subTLV is in the captured data */
    ND_TCHECK2(*(tptr), stlv_len);

    switch (stlv_type)
    {
      case ISIS_SUBTLV_SPB_INSTANCE:
          if (stlv_len < ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN)
            goto trunc;

          ND_PRINT((ndo, "\n\t        CIST Root-ID: %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, " %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, ", Path Cost: %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, ", Prio: %d", EXTRACT_16BITS(tptr)));
          tptr = tptr + 2;
          ND_PRINT((ndo, "\n\t        RES: %d",
                    EXTRACT_16BITS(tptr) >> 5));
          ND_PRINT((ndo, ", V: %d",
                    (EXTRACT_16BITS(tptr) >> 4) & 0x0001));
          ND_PRINT((ndo, ", SPSource-ID: %d",
                    (EXTRACT_32BITS(tptr) & 0x000fffff)));
          tptr = tptr+4;
          ND_PRINT((ndo, ", No of Trees: %x", *(tptr)));

          tmp = *(tptr++);

          len = len - ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN;
          stlv_len = stlv_len - ISIS_SUBTLV_SPB_INSTANCE_MIN_LEN;

          while (tmp)
          {
            if (stlv_len < ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN)
              goto trunc;

            ND_PRINT((ndo, "\n\t         U:%d, M:%d, A:%d, RES:%d",
                      *(tptr) >> 7, (*(tptr) >> 6) & 0x01,
                      (*(tptr) >> 5) & 0x01, (*(tptr) & 0x1f)));

            tptr++;

            ND_PRINT((ndo, ", ECT: %08x", EXTRACT_32BITS(tptr)));

            tptr = tptr + 4;

            ND_PRINT((ndo, ", BVID: %d, SPVID: %d",
                      (EXTRACT_24BITS(tptr) >> 12) & 0x000fff,
                      EXTRACT_24BITS(tptr) & 0x000fff));

            tptr = tptr + 3;
            len = len - ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN;
            stlv_len = stlv_len - ISIS_SUBTLV_SPB_INSTANCE_VLAN_TUPLE_LEN;
            tmp--;
          }

          break;

      case ISIS_SUBTLV_SPBM_SI:
          if (stlv_len < 8)
            goto trunc;

          ND_PRINT((ndo, "\n\t        BMAC: %08x", EXTRACT_32BITS(tptr)));
          tptr = tptr+4;
          ND_PRINT((ndo, "%04x", EXTRACT_16BITS(tptr)));
          tptr = tptr+2;

          ND_PRINT((ndo, ", RES: %d, VID: %d", EXTRACT_16BITS(tptr) >> 12,
                    (EXTRACT_16BITS(tptr)) & 0x0fff));

          tptr = tptr+2;
          len = len - 8;
          stlv_len = stlv_len - 8;

          while (stlv_len >= 4) {
            ND_TCHECK2(*tptr, 4);
            ND_PRINT((ndo, "\n\t        T: %d, R: %d, RES: %d, ISID: %d",
                    (EXTRACT_32BITS(tptr) >> 31),
                    (EXTRACT_32BITS(tptr) >> 30) & 0x01,
                    (EXTRACT_32BITS(tptr) >> 24) & 0x03f,
                    (EXTRACT_32BITS(tptr)) & 0x0ffffff));

            tptr = tptr + 4;
            len = len - 4;
            stlv_len = stlv_len - 4;
          }

        break;

      default:
        break;
    }
    tptr += stlv_len;
    len -= stlv_len;
  }
  return 0;

  trunc:
    ND_PRINT((ndo, "\n\t\t"));
    ND_PRINT((ndo, "%s", tstr));
    return(1);
}