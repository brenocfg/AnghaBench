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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct m3ua_param_header {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int const) ; 
 int /*<<< orphan*/  ParamName ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tag_value_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
m3ua_tags_print(netdissect_options *ndo,
                const u_char *buf, const u_int size)
{
  const u_char *p = buf;
  int align;
  uint16_t hdr_tag;
  uint16_t hdr_len;

  while (p < buf + size) {
    if (p + sizeof(struct m3ua_param_header) > buf + size)
      goto invalid;
    ND_TCHECK2(*p, sizeof(struct m3ua_param_header));
    /* Parameter Tag */
    hdr_tag = EXTRACT_16BITS(p);
    ND_PRINT((ndo, "\n\t\t\t%s: ", tok2str(ParamName, "Unknown Parameter (0x%04x)", hdr_tag)));
    /* Parameter Length */
    hdr_len = EXTRACT_16BITS(p + 2);
    if (hdr_len < sizeof(struct m3ua_param_header))
      goto invalid;
    /* Parameter Value */
    align = (p + hdr_len - buf) % 4;
    align = align ? 4 - align : 0;
    ND_TCHECK2(*p, hdr_len + align);
    tag_value_print(ndo, p, hdr_tag, hdr_len - sizeof(struct m3ua_param_header));
    p += hdr_len + align;
  }
  return;

invalid:
  ND_PRINT((ndo, "%s", istr));
  ND_TCHECK2(*buf, size);
  return;
trunc:
  ND_PRINT((ndo, "%s", tstr));
}