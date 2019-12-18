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
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  M_SMBTEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_E (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_strtouni (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int strlen (int /*<<< orphan*/  const*) ; 

int
smb_ntencrypt(const u_char *apwd, u_char *C8, u_char *RN)
{
	u_char S21[21];
	u_int16_t *unipwd;
	MD4_CTX *ctxp;
	u_int len;

	len = strlen(apwd);
	unipwd = malloc((len + 1) * sizeof(u_int16_t), M_SMBTEMP, M_WAITOK);
	/*
	 * S21 = concat(MD4(U(apwd)), zeros(5));
	 */
	smb_strtouni(unipwd, apwd);
	ctxp = malloc(sizeof(MD4_CTX), M_SMBTEMP, M_WAITOK);
	MD4Init(ctxp);
	MD4Update(ctxp, (u_char*)unipwd, len * sizeof(u_int16_t));
	free(unipwd, M_SMBTEMP);
	bzero(S21, 21);
	MD4Final(S21, ctxp);
	free(ctxp, M_SMBTEMP);

	smb_E(S21, C8, RN);
	smb_E(S21 + 7, C8, RN + 8);
	smb_E(S21 + 14, C8, RN + 16);
	return 0;
}