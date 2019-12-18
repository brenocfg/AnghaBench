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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  smb_fdata (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicodestr ; 

__attribute__((used)) static void
print_ipc(netdissect_options *ndo,
          const u_char *param, int paramlen, const u_char *data, int datalen)
{
    if (paramlen)
	smb_fdata(ndo, param, "Command=[w]\nStr1=[S]\nStr2=[S]\n", param + paramlen,
	    unicodestr);
    if (datalen)
	smb_fdata(ndo, data, "IPC ", data + datalen, unicodestr);
}