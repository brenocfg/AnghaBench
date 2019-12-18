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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ request ; 
 int /*<<< orphan*/  smb_fdata (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_print_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  unicodestr ; 

__attribute__((used)) static void
trans2_findfirst(netdissect_options *ndo,
                 const u_char *param, const u_char *data, int pcnt, int dcnt)
{
    const char *fmt;

    if (request)
	fmt = "Attribute=[A]\nSearchCount=[d]\nFlags=[w]\nLevel=[dP4]\nFile=[S]\n";
    else
	fmt = "Handle=[w]\nCount=[d]\nEOS=[w]\nEoffset=[d]\nLastNameOfs=[w]\n";

    smb_fdata(ndo, param, fmt, param + pcnt, unicodestr);
    if (dcnt) {
	ND_PRINT((ndo, "data:\n"));
	smb_print_data(ndo, data, dcnt);
    }
}