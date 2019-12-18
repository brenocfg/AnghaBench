#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ND_TCHECK_16BITS (int const*) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  opcode_str ; 
 int* smb_fdata (TYPE_1__*,int const*,char*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_print_data (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int const* startbuf ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
nbt_udp137_print(netdissect_options *ndo,
                 const u_char *data, int length)
{
    const u_char *maxbuf = data + length;
    int name_trn_id, response, opcode, nm_flags, rcode;
    int qdcount, ancount, nscount, arcount;
    const u_char *p;
    int total, i;

    ND_TCHECK2(data[10], 2);
    name_trn_id = EXTRACT_16BITS(data);
    response = (data[2] >> 7);
    opcode = (data[2] >> 3) & 0xF;
    nm_flags = ((data[2] & 0x7) << 4) + (data[3] >> 4);
    rcode = data[3] & 0xF;
    qdcount = EXTRACT_16BITS(data + 4);
    ancount = EXTRACT_16BITS(data + 6);
    nscount = EXTRACT_16BITS(data + 8);
    arcount = EXTRACT_16BITS(data + 10);
    startbuf = data;

    if (maxbuf <= data)
	return;

    if (ndo->ndo_vflag > 1)
	ND_PRINT((ndo, "\n>>> "));

    ND_PRINT((ndo, "NBT UDP PACKET(137): %s", tok2str(opcode_str, "OPUNKNOWN", opcode)));
    if (response) {
        ND_PRINT((ndo, "; %s", rcode ? "NEGATIVE" : "POSITIVE"));
    }
    ND_PRINT((ndo, "; %s; %s", response ? "RESPONSE" : "REQUEST",
              (nm_flags & 1) ? "BROADCAST" : "UNICAST"));

    if (ndo->ndo_vflag < 2)
	return;

    ND_PRINT((ndo, "\nTrnID=0x%X\nOpCode=%d\nNmFlags=0x%X\nRcode=%d\nQueryCount=%d\nAnswerCount=%d\nAuthorityCount=%d\nAddressRecCount=%d\n",
	name_trn_id, opcode, nm_flags, rcode, qdcount, ancount, nscount,
	arcount));

    p = data + 12;

    total = ancount + nscount + arcount;

    if (qdcount > 100 || total > 100) {
	ND_PRINT((ndo, "Corrupt packet??\n"));
	return;
    }

    if (qdcount) {
	ND_PRINT((ndo, "QuestionRecords:\n"));
	for (i = 0; i < qdcount; i++) {
	    p = smb_fdata(ndo, p,
		"|Name=[n1]\nQuestionType=[rw]\nQuestionClass=[rw]\n#",
		maxbuf, 0);
	    if (p == NULL)
		goto out;
	}
    }

    if (total) {
	ND_PRINT((ndo, "\nResourceRecords:\n"));
	for (i = 0; i < total; i++) {
	    int rdlen;
	    int restype;

	    p = smb_fdata(ndo, p, "Name=[n1]\n#", maxbuf, 0);
	    if (p == NULL)
		goto out;
	    ND_TCHECK_16BITS(p);
	    restype = EXTRACT_16BITS(p);
	    p = smb_fdata(ndo, p, "ResType=[rw]\nResClass=[rw]\nTTL=[rD]\n", p + 8, 0);
	    if (p == NULL)
		goto out;
	    ND_TCHECK_16BITS(p);
	    rdlen = EXTRACT_16BITS(p);
	    ND_PRINT((ndo, "ResourceLength=%d\nResourceData=\n", rdlen));
	    p += 2;
	    if (rdlen == 6) {
		p = smb_fdata(ndo, p, "AddrType=[rw]\nAddress=[b.b.b.b]\n", p + rdlen, 0);
		if (p == NULL)
		    goto out;
	    } else {
		if (restype == 0x21) {
		    int numnames;

		    ND_TCHECK(*p);
		    numnames = p[0];
		    p = smb_fdata(ndo, p, "NumNames=[B]\n", p + 1, 0);
		    if (p == NULL)
			goto out;
		    while (numnames--) {
			p = smb_fdata(ndo, p, "Name=[n2]\t#", maxbuf, 0);
			if (p == NULL)
			    goto out;
			ND_TCHECK(*p);
			if (p[0] & 0x80)
			    ND_PRINT((ndo, "<GROUP> "));
			switch (p[0] & 0x60) {
			case 0x00: ND_PRINT((ndo, "B ")); break;
			case 0x20: ND_PRINT((ndo, "P ")); break;
			case 0x40: ND_PRINT((ndo, "M ")); break;
			case 0x60: ND_PRINT((ndo, "_ ")); break;
			}
			if (p[0] & 0x10)
			    ND_PRINT((ndo, "<DEREGISTERING> "));
			if (p[0] & 0x08)
			    ND_PRINT((ndo, "<CONFLICT> "));
			if (p[0] & 0x04)
			    ND_PRINT((ndo, "<ACTIVE> "));
			if (p[0] & 0x02)
			    ND_PRINT((ndo, "<PERMANENT> "));
			ND_PRINT((ndo, "\n"));
			p += 2;
		    }
		} else {
		    smb_print_data(ndo, p, min(rdlen, length - (p - data)));
		    p += rdlen;
		}
	    }
	}
    }

    if (p < maxbuf)
	smb_fdata(ndo, p, "AdditionalData:\n", maxbuf, 0);

out:
    ND_PRINT((ndo, "\n"));
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}