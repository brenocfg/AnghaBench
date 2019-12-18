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
typedef  int /*<<< orphan*/  const u_char ;
struct TYPE_6__ {int ndo_vflag; int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  print_smb (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* smb_fdata (TYPE_1__*,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* startbuf ; 

void
nbt_udp138_print(netdissect_options *ndo,
                 const u_char *data, int length)
{
    const u_char *maxbuf = data + length;

    if (maxbuf > ndo->ndo_snapend)
	maxbuf = ndo->ndo_snapend;
    if (maxbuf <= data)
	return;
    startbuf = data;

    if (ndo->ndo_vflag < 2) {
	ND_PRINT((ndo, "NBT UDP PACKET(138)"));
	return;
    }

    data = smb_fdata(ndo, data,
	"\n>>> NBT UDP PACKET(138) Res=[rw] ID=[rw] IP=[b.b.b.b] Port=[rd] Length=[rd] Res2=[rw]\nSourceName=[n1]\nDestName=[n1]\n#",
	maxbuf, 0);

    if (data != NULL) {
	/* If there isn't enough data for "\377SMB", don't check for it. */
	if (&data[3] >= maxbuf)
	    goto out;

	if (memcmp(data, "\377SMB",4) == 0)
	    print_smb(ndo, data, maxbuf);
    }
out:
    ND_PRINT((ndo, "\n"));
}