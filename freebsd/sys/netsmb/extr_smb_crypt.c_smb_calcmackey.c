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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct smb_vc {int vc_hflags2; int vc_mackeylen; int /*<<< orphan*/ * vc_mackey; int /*<<< orphan*/  vc_ch; scalar_t__ vc_seqno; } ;
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MD4Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  M_SMBTEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SMB_FLAGS2_SECURITY_SIGNATURE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_E (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_strtouni (int /*<<< orphan*/ *,char const*) ; 
 char* smb_vc_getpass (struct smb_vc*) ; 
 int strlen (char const*) ; 

int
smb_calcmackey(struct smb_vc *vcp)
{
	const char *pwd;
	u_int16_t *unipwd;
	u_int len;
	MD4_CTX md4;
	u_char S16[16], S21[21];

	KASSERT(vcp->vc_hflags2 & SMB_FLAGS2_SECURITY_SIGNATURE,
	    ("signatures not enabled"));

	if (vcp->vc_mackey != NULL) {
		free(vcp->vc_mackey, M_SMBTEMP);
		vcp->vc_mackey = NULL;
		vcp->vc_mackeylen = 0;
		vcp->vc_seqno = 0;
	}

	/*
	 * The partial MAC key is the concatenation of the 16 byte session
	 * key and the 24 byte challenge response.
	 */
	vcp->vc_mackeylen = 16 + 24;
	vcp->vc_mackey = malloc(vcp->vc_mackeylen, M_SMBTEMP, M_WAITOK);

	/*
	 * Calculate session key:
	 *	MD4(MD4(U(PN)))
	 */
	pwd = smb_vc_getpass(vcp);
	len = strlen(pwd);
	unipwd = malloc((len + 1) * sizeof(u_int16_t), M_SMBTEMP, M_WAITOK);
	smb_strtouni(unipwd, pwd);
	MD4Init(&md4);
	MD4Update(&md4, (u_char *)unipwd, len * sizeof(u_int16_t));
	MD4Final(S16, &md4);
	MD4Init(&md4);
	MD4Update(&md4, S16, 16);
	MD4Final(vcp->vc_mackey, &md4);
	free(unipwd, M_SMBTEMP);

	/*
	 * Calculate response to challenge:
	 *	Ex(concat(MD4(U(pass)), zeros(5)), C8)
	 */
	bzero(S21, 21);
	bcopy(S16, S21, 16);
	smb_E(S21, vcp->vc_ch, vcp->vc_mackey + 16);
	smb_E(S21 + 7, vcp->vc_ch, vcp->vc_mackey + 24);
	smb_E(S21 + 14, vcp->vc_ch, vcp->vc_mackey + 32);

	return (0);
}