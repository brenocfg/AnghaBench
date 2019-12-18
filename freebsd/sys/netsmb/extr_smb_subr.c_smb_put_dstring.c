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
struct smb_vc {int dummy; } ;
struct mbchain {int dummy; } ;

/* Variables and functions */
 scalar_t__ SMB_UNICODE_STRINGS (struct smb_vc*) ; 
 int mb_put_uint16le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int mb_put_uint8 (struct mbchain*,int /*<<< orphan*/ ) ; 
 int smb_put_dmem (struct mbchain*,struct smb_vc*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
smb_put_dstring(struct mbchain *mbp, struct smb_vc *vcp, const char *src,
	int caseopt)
{
	int error;

	error = smb_put_dmem(mbp, vcp, src, strlen(src), caseopt);
	if (error)
		return error;
	if (SMB_UNICODE_STRINGS(vcp))
		return mb_put_uint16le(mbp, 0);
	return mb_put_uint8(mbp, 0);
}