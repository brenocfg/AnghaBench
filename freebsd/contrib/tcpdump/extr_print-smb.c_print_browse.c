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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int* smb_fdata (int /*<<< orphan*/ *,int const*,char*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 
 int /*<<< orphan*/  unicodestr ; 

__attribute__((used)) static void
print_browse(netdissect_options *ndo,
             const u_char *param, int paramlen, const u_char *data, int datalen)
{
    const u_char *maxbuf = data + datalen;
    int command;

    ND_TCHECK(data[0]);
    command = data[0];

    smb_fdata(ndo, param, "BROWSE PACKET\n|Param ", param+paramlen, unicodestr);

    switch (command) {
    case 0xF:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (LocalMasterAnnouncement)\nUpdateCount=[w]\nRes1=[B]\nAnnounceInterval=[d]\nName=[n2]\nMajorVersion=[B]\nMinorVersion=[B]\nServerType=[W]\nElectionVersion=[w]\nBrowserConstant=[w]\n",
	    maxbuf, unicodestr);
	break;

    case 0x1:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (HostAnnouncement)\nUpdateCount=[w]\nRes1=[B]\nAnnounceInterval=[d]\nName=[n2]\nMajorVersion=[B]\nMinorVersion=[B]\nServerType=[W]\nElectionVersion=[w]\nBrowserConstant=[w]\n",
	    maxbuf, unicodestr);
	break;

    case 0x2:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (AnnouncementRequest)\nFlags=[B]\nReplySystemName=[S]\n",
	    maxbuf, unicodestr);
	break;

    case 0xc:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (WorkgroupAnnouncement)\nUpdateCount=[w]\nRes1=[B]\nAnnounceInterval=[d]\nName=[n2]\nMajorVersion=[B]\nMinorVersion=[B]\nServerType=[W]\nCommentPointer=[W]\nServerName=[S]\n",
	    maxbuf, unicodestr);
	break;

    case 0x8:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (ElectionFrame)\nElectionVersion=[B]\nOSSummary=[W]\nUptime=[(W, W)]\nServerName=[S]\n",
	    maxbuf, unicodestr);
	break;

    case 0xb:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (BecomeBackupBrowser)\nName=[S]\n",
	    maxbuf, unicodestr);
	break;

    case 0x9:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (GetBackupList)\nListCount?=[B]\nToken=[W]\n",
	    maxbuf, unicodestr);
	break;

    case 0xa:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (BackupListResponse)\nServerCount?=[B]\nToken=[W]\n*Name=[S]\n",
	    maxbuf, unicodestr);
	break;

    case 0xd:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (MasterAnnouncement)\nMasterName=[S]\n",
	    maxbuf, unicodestr);
	break;

    case 0xe:
	data = smb_fdata(ndo, data,
	    "BROWSE PACKET:\nType=[B] (ResetBrowser)\nOptions=[B]\n", maxbuf, unicodestr);
	break;

    default:
	data = smb_fdata(ndo, data, "Unknown Browser Frame ", maxbuf, unicodestr);
	break;
    }
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}