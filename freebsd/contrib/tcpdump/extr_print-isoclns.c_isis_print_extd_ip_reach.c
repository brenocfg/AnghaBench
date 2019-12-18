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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int u_int ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  ident_buffer ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 scalar_t__ ISIS_MASK_TLV_EXTD_IP6_IE (int) ; 
 scalar_t__ ISIS_MASK_TLV_EXTD_IP6_SUBTLV (int) ; 
 scalar_t__ ISIS_MASK_TLV_EXTD_IP_SUBTLV (int) ; 
 scalar_t__ ISIS_MASK_TLV_EXTD_IP_UPDOWN (int) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isis_print_ip_reach_subtlv (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static int
isis_print_extd_ip_reach(netdissect_options *ndo,
                         const uint8_t *tptr, const char *ident, uint16_t afi)
{
    char ident_buffer[20];
    uint8_t prefix[sizeof(struct in6_addr)]; /* shared copy buffer for IPv4 and IPv6 prefixes */
    u_int metric, status_byte, bit_length, byte_length, sublen, processed, subtlvtype, subtlvlen;

    if (!ND_TTEST2(*tptr, 4))
        return (0);
    metric = EXTRACT_32BITS(tptr);
    processed=4;
    tptr+=4;

    if (afi == AF_INET) {
        if (!ND_TTEST2(*tptr, 1)) /* fetch status byte */
            return (0);
        status_byte=*(tptr++);
        bit_length = status_byte&0x3f;
        if (bit_length > 32) {
            ND_PRINT((ndo, "%sIPv4 prefix: bad bit length %u",
                   ident,
                   bit_length));
            return (0);
        }
        processed++;
    } else if (afi == AF_INET6) {
        if (!ND_TTEST2(*tptr, 2)) /* fetch status & prefix_len byte */
            return (0);
        status_byte=*(tptr++);
        bit_length=*(tptr++);
        if (bit_length > 128) {
            ND_PRINT((ndo, "%sIPv6 prefix: bad bit length %u",
                   ident,
                   bit_length));
            return (0);
        }
        processed+=2;
    } else
        return (0); /* somebody is fooling us */

    byte_length = (bit_length + 7) / 8; /* prefix has variable length encoding */

    if (!ND_TTEST2(*tptr, byte_length))
        return (0);
    memset(prefix, 0, sizeof prefix);   /* clear the copy buffer */
    memcpy(prefix,tptr,byte_length);    /* copy as much as is stored in the TLV */
    tptr+=byte_length;
    processed+=byte_length;

    if (afi == AF_INET)
        ND_PRINT((ndo, "%sIPv4 prefix: %15s/%u",
               ident,
               ipaddr_string(ndo, prefix),
               bit_length));
    else if (afi == AF_INET6)
        ND_PRINT((ndo, "%sIPv6 prefix: %s/%u",
               ident,
               ip6addr_string(ndo, prefix),
               bit_length));

    ND_PRINT((ndo, ", Distribution: %s, Metric: %u",
           ISIS_MASK_TLV_EXTD_IP_UPDOWN(status_byte) ? "down" : "up",
           metric));

    if (afi == AF_INET && ISIS_MASK_TLV_EXTD_IP_SUBTLV(status_byte))
        ND_PRINT((ndo, ", sub-TLVs present"));
    else if (afi == AF_INET6)
        ND_PRINT((ndo, ", %s%s",
               ISIS_MASK_TLV_EXTD_IP6_IE(status_byte) ? "External" : "Internal",
               ISIS_MASK_TLV_EXTD_IP6_SUBTLV(status_byte) ? ", sub-TLVs present" : ""));

    if ((afi == AF_INET  && ISIS_MASK_TLV_EXTD_IP_SUBTLV(status_byte))
     || (afi == AF_INET6 && ISIS_MASK_TLV_EXTD_IP6_SUBTLV(status_byte))
	) {
        /* assume that one prefix can hold more
           than one subTLV - therefore the first byte must reflect
           the aggregate bytecount of the subTLVs for this prefix
        */
        if (!ND_TTEST2(*tptr, 1))
            return (0);
        sublen=*(tptr++);
        processed+=sublen+1;
        ND_PRINT((ndo, " (%u)", sublen));   /* print out subTLV length */

        while (sublen>0) {
            if (!ND_TTEST2(*tptr,2))
                return (0);
            subtlvtype=*(tptr++);
            subtlvlen=*(tptr++);
            /* prepend the indent string */
            snprintf(ident_buffer, sizeof(ident_buffer), "%s  ",ident);
            if (!isis_print_ip_reach_subtlv(ndo, tptr, subtlvtype, subtlvlen, ident_buffer))
                return(0);
            tptr+=subtlvlen;
            sublen-=(subtlvlen+2);
        }
    }
    return (processed);
}