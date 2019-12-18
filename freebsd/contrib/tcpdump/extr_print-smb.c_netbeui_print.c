#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_char ;
struct TYPE_7__ {int const* ndo_snapend; int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;
struct TYPE_8__ {char* nonverbose; char* verbose; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EXTRACT_LE_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 TYPE_5__* nbf_strings ; 
 int /*<<< orphan*/  print_smb (TYPE_1__*,int const*,int const*) ; 
 int* smb_fdata (TYPE_1__*,int const*,char*,int const*,int /*<<< orphan*/ ) ; 
 int const* startbuf ; 
 int /*<<< orphan*/  tstr ; 

void
netbeui_print(netdissect_options *ndo,
              u_short control, const u_char *data, int length)
{
    const u_char *maxbuf = data + length;
    int len;
    int command;
    const u_char *data2;
    int is_truncated = 0;

    if (maxbuf > ndo->ndo_snapend)
	maxbuf = ndo->ndo_snapend;
    ND_TCHECK(data[4]);
    len = EXTRACT_LE_16BITS(data);
    command = data[4];
    data2 = data + len;
    if (data2 >= maxbuf) {
	data2 = maxbuf;
	is_truncated = 1;
    }

    startbuf = data;

    if (ndo->ndo_vflag < 2) {
	ND_PRINT((ndo, "NBF Packet: "));
	data = smb_fdata(ndo, data, "[P5]#", maxbuf, 0);
    } else {
	ND_PRINT((ndo, "\n>>> NBF Packet\nType=0x%X ", control));
	data = smb_fdata(ndo, data, "Length=[d] Signature=[w] Command=[B]\n#", maxbuf, 0);
    }
    if (data == NULL)
	goto out;

    if (command > 0x1f || nbf_strings[command].name == NULL) {
	if (ndo->ndo_vflag < 2)
	    data = smb_fdata(ndo, data, "Unknown NBF Command#", data2, 0);
	else
	    data = smb_fdata(ndo, data, "Unknown NBF Command\n", data2, 0);
    } else {
	if (ndo->ndo_vflag < 2) {
	    ND_PRINT((ndo, "%s", nbf_strings[command].name));
	    if (nbf_strings[command].nonverbose != NULL)
		data = smb_fdata(ndo, data, nbf_strings[command].nonverbose, data2, 0);
	} else {
	    ND_PRINT((ndo, "%s:\n", nbf_strings[command].name));
	    if (nbf_strings[command].verbose != NULL)
		data = smb_fdata(ndo, data, nbf_strings[command].verbose, data2, 0);
	    else
		ND_PRINT((ndo, "\n"));
	}
    }

    if (ndo->ndo_vflag < 2)
	return;

    if (data == NULL)
	goto out;

    if (is_truncated) {
	/* data2 was past the end of the buffer */
	goto out;
    }

    /* If this isn't a command that would contain an SMB message, quit. */
    if (command != 0x08 && command != 0x09 && command != 0x15 &&
        command != 0x16)
	goto out;

    /* If there isn't enough data for "\377SMB", don't look for it. */
    if (&data2[3] >= maxbuf)
	goto out;

    if (memcmp(data2, "\377SMB",4) == 0)
	print_smb(ndo, data2, maxbuf);
    else {
	int i;
	for (i = 0; i < 128; i++) {
	    if (&data2[i + 3] >= maxbuf)
		break;
	    if (memcmp(&data2[i], "\377SMB", 4) == 0) {
		ND_PRINT((ndo, "found SMB packet at %d\n", i));
		print_smb(ndo, &data2[i], maxbuf);
		break;
	    }
	}
    }

out:
    ND_PRINT((ndo, "\n"));
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}