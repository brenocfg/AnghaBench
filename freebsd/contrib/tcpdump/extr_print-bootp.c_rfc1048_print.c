#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  us ;
typedef  int /*<<< orphan*/  ul ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int u_int ;
typedef  scalar_t__ u_char ;
struct TYPE_7__ {int ndo_vflag; int /*<<< orphan*/  ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  AGENT_SUBOPTION_CIRCUIT_ID 138 
#define  AGENT_SUBOPTION_REMOTE_ID 137 
#define  AGENT_SUBOPTION_SUBSCRIBER_ID 136 
 scalar_t__ EXTRACT_16BITS (scalar_t__ const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (scalar_t__ const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (scalar_t__ const,int) ; 
 scalar_t__ ND_TTEST2 (scalar_t__ const,int) ; 
#define  TAG_AGENT_CIRCUIT 135 
#define  TAG_CLASSLESS_STATIC_RT 134 
#define  TAG_CLASSLESS_STA_RT_MS 133 
#define  TAG_CLIENT_FQDN 132 
#define  TAG_CLIENT_ID 131 
 scalar_t__ TAG_DHCP_MESSAGE ; 
 scalar_t__ TAG_END ; 
 scalar_t__ TAG_EXTENDED_OPTION ; 
 scalar_t__ TAG_EXTENDED_REQUEST ; 
#define  TAG_NETBIOS_NODE 130 
#define  TAG_OPT_OVERLOAD 129 
 scalar_t__ TAG_PAD ; 
 scalar_t__ TAG_PARM_REQUEST ; 
#define  TAG_USER_CLASS 128 
 int /*<<< orphan*/  agent_suboption_values ; 
 int /*<<< orphan*/  arp2str ; 
 int /*<<< orphan*/  client_fqdn_flags (scalar_t__ const) ; 
 int /*<<< orphan*/  dhcp_msg_values ; 
 int /*<<< orphan*/  fn_printn (TYPE_1__*,scalar_t__ const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  nbo2str ; 
 int /*<<< orphan*/  oo2str ; 
 int /*<<< orphan*/  print_unknown_data (TYPE_1__*,scalar_t__ const*,char*,int) ; 
 int /*<<< orphan*/  tag2str ; 
 char* tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xtag2str ; 

__attribute__((used)) static void
rfc1048_print(netdissect_options *ndo,
	      register const u_char *bp)
{
	register uint16_t tag;
	register u_int len;
	register const char *cp;
	register char c;
	int first, idx;
	uint32_t ul;
	uint16_t us;
	uint8_t uc, subopt, suboptlen;

	ND_PRINT((ndo, "\n\t  Vendor-rfc1048 Extensions"));

	/* Step over magic cookie */
	ND_PRINT((ndo, "\n\t    Magic Cookie 0x%08x", EXTRACT_32BITS(bp)));
	bp += sizeof(int32_t);

	/* Loop while we there is a tag left in the buffer */
	while (ND_TTEST2(*bp, 1)) {
		tag = *bp++;
		if (tag == TAG_PAD && ndo->ndo_vflag < 3)
			continue;
		if (tag == TAG_END && ndo->ndo_vflag < 3)
			return;
		if (tag == TAG_EXTENDED_OPTION) {
			ND_TCHECK2(*(bp + 1), 2);
			tag = EXTRACT_16BITS(bp + 1);
			/* XXX we don't know yet if the IANA will
			 * preclude overlap of 1-byte and 2-byte spaces.
			 * If not, we need to offset tag after this step.
			 */
			cp = tok2str(xtag2str, "?xT%u", tag);
		} else
			cp = tok2str(tag2str, "?T%u", tag);
		c = *cp++;

		if (tag == TAG_PAD || tag == TAG_END)
			len = 0;
		else {
			/* Get the length; check for truncation */
			ND_TCHECK2(*bp, 1);
			len = *bp++;
		}

		ND_PRINT((ndo, "\n\t    %s Option %u, length %u%s", cp, tag, len,
			  len > 0 ? ": " : ""));

		if (tag == TAG_PAD && ndo->ndo_vflag > 2) {
			u_int ntag = 1;
			while (ND_TTEST2(*bp, 1) && *bp == TAG_PAD) {
				bp++;
				ntag++;
			}
			if (ntag > 1)
				ND_PRINT((ndo, ", occurs %u", ntag));
		}

		if (!ND_TTEST2(*bp, len)) {
			ND_PRINT((ndo, "[|rfc1048 %u]", len));
			return;
		}

		if (tag == TAG_DHCP_MESSAGE && len == 1) {
			uc = *bp++;
			ND_PRINT((ndo, "%s", tok2str(dhcp_msg_values, "Unknown (%u)", uc)));
			continue;
		}

		if (tag == TAG_PARM_REQUEST) {
			idx = 0;
			while (len-- > 0) {
				uc = *bp++;
				cp = tok2str(tag2str, "?Option %u", uc);
				if (idx % 4 == 0)
					ND_PRINT((ndo, "\n\t      "));
				else
					ND_PRINT((ndo, ", "));
				ND_PRINT((ndo, "%s", cp + 1));
				idx++;
			}
			continue;
		}

		if (tag == TAG_EXTENDED_REQUEST) {
			first = 1;
			while (len > 1) {
				len -= 2;
				us = EXTRACT_16BITS(bp);
				bp += 2;
				cp = tok2str(xtag2str, "?xT%u", us);
				if (!first)
					ND_PRINT((ndo, "+"));
				ND_PRINT((ndo, "%s", cp + 1));
				first = 0;
			}
			continue;
		}

		/* Print data */
		if (c == '?') {
			/* Base default formats for unknown tags on data size */
			if (len & 1)
				c = 'b';
			else if (len & 2)
				c = 's';
			else
				c = 'l';
		}
		first = 1;
		switch (c) {

		case 'a':
			/* ascii strings */
			ND_PRINT((ndo, "\""));
			if (fn_printn(ndo, bp, len, ndo->ndo_snapend)) {
				ND_PRINT((ndo, "\""));
				goto trunc;
			}
			ND_PRINT((ndo, "\""));
			bp += len;
			len = 0;
			break;

		case 'i':
		case 'l':
		case 'L':
			/* ip addresses/32-bit words */
			while (len >= sizeof(ul)) {
				if (!first)
					ND_PRINT((ndo, ","));
				ul = EXTRACT_32BITS(bp);
				if (c == 'i') {
					ul = htonl(ul);
					ND_PRINT((ndo, "%s", ipaddr_string(ndo, &ul)));
				} else if (c == 'L')
					ND_PRINT((ndo, "%d", ul));
				else
					ND_PRINT((ndo, "%u", ul));
				bp += sizeof(ul);
				len -= sizeof(ul);
				first = 0;
			}
			break;

		case 'p':
			/* IP address pairs */
			while (len >= 2*sizeof(ul)) {
				if (!first)
					ND_PRINT((ndo, ","));
				memcpy((char *)&ul, (const char *)bp, sizeof(ul));
				ND_PRINT((ndo, "(%s:", ipaddr_string(ndo, &ul)));
				bp += sizeof(ul);
				memcpy((char *)&ul, (const char *)bp, sizeof(ul));
				ND_PRINT((ndo, "%s)", ipaddr_string(ndo, &ul)));
				bp += sizeof(ul);
				len -= 2*sizeof(ul);
				first = 0;
			}
			break;

		case 's':
			/* shorts */
			while (len >= sizeof(us)) {
				if (!first)
					ND_PRINT((ndo, ","));
				us = EXTRACT_16BITS(bp);
				ND_PRINT((ndo, "%u", us));
				bp += sizeof(us);
				len -= sizeof(us);
				first = 0;
			}
			break;

		case 'B':
			/* boolean */
			while (len > 0) {
				if (!first)
					ND_PRINT((ndo, ","));
				switch (*bp) {
				case 0:
					ND_PRINT((ndo, "N"));
					break;
				case 1:
					ND_PRINT((ndo, "Y"));
					break;
				default:
					ND_PRINT((ndo, "%u?", *bp));
					break;
				}
				++bp;
				--len;
				first = 0;
			}
			break;

		case 'b':
		case 'x':
		default:
			/* Bytes */
			while (len > 0) {
				if (!first)
					ND_PRINT((ndo, c == 'x' ? ":" : "."));
				if (c == 'x')
					ND_PRINT((ndo, "%02x", *bp));
				else
					ND_PRINT((ndo, "%u", *bp));
				++bp;
				--len;
				first = 0;
			}
			break;

		case '$':
			/* Guys we can't handle with one of the usual cases */
			switch (tag) {

			case TAG_NETBIOS_NODE:
				/* this option should be at least 1 byte long */
				if (len < 1) {
					ND_PRINT((ndo, "ERROR: length < 1 bytes"));
					break;
				}
				tag = *bp++;
				--len;
				ND_PRINT((ndo, "%s", tok2str(nbo2str, NULL, tag)));
				break;

			case TAG_OPT_OVERLOAD:
				/* this option should be at least 1 byte long */
				if (len < 1) {
					ND_PRINT((ndo, "ERROR: length < 1 bytes"));
					break;
				}
				tag = *bp++;
				--len;
				ND_PRINT((ndo, "%s", tok2str(oo2str, NULL, tag)));
				break;

			case TAG_CLIENT_FQDN:
				/* this option should be at least 3 bytes long */
				if (len < 3) {
					ND_PRINT((ndo, "ERROR: length < 3 bytes"));
					bp += len;
					len = 0;
					break;
				}
				if (*bp)
					ND_PRINT((ndo, "[%s] ", client_fqdn_flags(*bp)));
				bp++;
				if (*bp || *(bp+1))
					ND_PRINT((ndo, "%u/%u ", *bp, *(bp+1)));
				bp += 2;
				ND_PRINT((ndo, "\""));
				if (fn_printn(ndo, bp, len - 3, ndo->ndo_snapend)) {
					ND_PRINT((ndo, "\""));
					goto trunc;
				}
				ND_PRINT((ndo, "\""));
				bp += len - 3;
				len = 0;
				break;

			case TAG_CLIENT_ID:
			    {
				int type;

				/* this option should be at least 1 byte long */
				if (len < 1) {
					ND_PRINT((ndo, "ERROR: length < 1 bytes"));
					break;
				}
				type = *bp++;
				len--;
				if (type == 0) {
					ND_PRINT((ndo, "\""));
					if (fn_printn(ndo, bp, len, ndo->ndo_snapend)) {
						ND_PRINT((ndo, "\""));
						goto trunc;
					}
					ND_PRINT((ndo, "\""));
					bp += len;
					len = 0;
					break;
				} else {
					ND_PRINT((ndo, "%s ", tok2str(arp2str, "hardware-type %u,", type)));
					while (len > 0) {
						if (!first)
							ND_PRINT((ndo, ":"));
						ND_PRINT((ndo, "%02x", *bp));
						++bp;
						--len;
						first = 0;
					}
				}
				break;
			    }

			case TAG_AGENT_CIRCUIT:
				while (len >= 2) {
					subopt = *bp++;
					suboptlen = *bp++;
					len -= 2;
					if (suboptlen > len) {
						ND_PRINT((ndo, "\n\t      %s SubOption %u, length %u: length goes past end of option",
							  tok2str(agent_suboption_values, "Unknown", subopt),
							  subopt,
							  suboptlen));
						bp += len;
						len = 0;
						break;
					}
					ND_PRINT((ndo, "\n\t      %s SubOption %u, length %u: ",
						  tok2str(agent_suboption_values, "Unknown", subopt),
						  subopt,
						  suboptlen));
					switch (subopt) {

					case AGENT_SUBOPTION_CIRCUIT_ID: /* fall through */
					case AGENT_SUBOPTION_REMOTE_ID:
					case AGENT_SUBOPTION_SUBSCRIBER_ID:
						if (fn_printn(ndo, bp, suboptlen, ndo->ndo_snapend))
							goto trunc;
						break;

					default:
						print_unknown_data(ndo, bp, "\n\t\t", suboptlen);
					}

					len -= suboptlen;
					bp += suboptlen;
				}
				break;

			case TAG_CLASSLESS_STATIC_RT:
			case TAG_CLASSLESS_STA_RT_MS:
			    {
				u_int mask_width, significant_octets, i;

				/* this option should be at least 5 bytes long */
				if (len < 5) {
					ND_PRINT((ndo, "ERROR: length < 5 bytes"));
					bp += len;
					len = 0;
					break;
				}
				while (len > 0) {
					if (!first)
						ND_PRINT((ndo, ","));
					mask_width = *bp++;
					len--;
					/* mask_width <= 32 */
					if (mask_width > 32) {
						ND_PRINT((ndo, "[ERROR: Mask width (%d) > 32]", mask_width));
						bp += len;
						len = 0;
						break;
					}
					significant_octets = (mask_width + 7) / 8;
					/* significant octets + router(4) */
					if (len < significant_octets + 4) {
						ND_PRINT((ndo, "[ERROR: Remaining length (%u) < %u bytes]", len, significant_octets + 4));
						bp += len;
						len = 0;
						break;
					}
					ND_PRINT((ndo, "("));
					if (mask_width == 0)
						ND_PRINT((ndo, "default"));
					else {
						for (i = 0; i < significant_octets ; i++) {
							if (i > 0)
								ND_PRINT((ndo, "."));
							ND_PRINT((ndo, "%d", *bp++));
						}
						for (i = significant_octets ; i < 4 ; i++)
							ND_PRINT((ndo, ".0"));
						ND_PRINT((ndo, "/%d", mask_width));
					}
					memcpy((char *)&ul, (const char *)bp, sizeof(ul));
					ND_PRINT((ndo, ":%s)", ipaddr_string(ndo, &ul)));
					bp += sizeof(ul);
					len -= (significant_octets + 4);
					first = 0;
				}
				break;
			    }

			case TAG_USER_CLASS:
			    {
				u_int suboptnumber = 1;

				first = 1;
				if (len < 2) {
					ND_PRINT((ndo, "ERROR: length < 2 bytes"));
					bp += len;
					len = 0;
					break;
				}
				while (len > 0) {
					suboptlen = *bp++;
					len--;
					ND_PRINT((ndo, "\n\t      "));
					ND_PRINT((ndo, "instance#%u: ", suboptnumber));
					if (suboptlen == 0) {
						ND_PRINT((ndo, "ERROR: suboption length must be non-zero"));
						bp += len;
						len = 0;
						break;
					}
					if (len < suboptlen) {
						ND_PRINT((ndo, "ERROR: invalid option"));
						bp += len;
						len = 0;
						break;
					}
					ND_PRINT((ndo, "\""));
					if (fn_printn(ndo, bp, suboptlen, ndo->ndo_snapend)) {
						ND_PRINT((ndo, "\""));
						goto trunc;
					}
					ND_PRINT((ndo, "\""));
					ND_PRINT((ndo, ", length %d", suboptlen));
					suboptnumber++;
					len -= suboptlen;
					bp += suboptlen;
				}
				break;
			    }

			default:
				ND_PRINT((ndo, "[unknown special tag %u, size %u]",
					  tag, len));
				bp += len;
				len = 0;
				break;
			}
			break;
		}
		/* Data left over? */
		if (len) {
			ND_PRINT((ndo, "\n\t  trailing data length %u", len));
			bp += len;
		}
	}
	return;
trunc:
	ND_PRINT((ndo, "|[rfc1048]"));
}