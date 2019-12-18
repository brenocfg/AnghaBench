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

/* Variables and functions */
 int /*<<< orphan*/  M_SMBTEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * N8 ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_E (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/  const*) ; 

int
smb_encrypt(const u_char *apwd, u_char *C8, u_char *RN)
{
	u_char *p, *P14, *S21;

	p = malloc(14 + 21, M_SMBTEMP, M_WAITOK);
	bzero(p, 14 + 21);
	P14 = p;
	S21 = p + 14;
	bcopy(apwd, P14, min(14, strlen(apwd)));
	/*
	 * S21 = concat(Ex(P14, N8), zeros(5));
	 */
	smb_E(P14, N8, S21);
	smb_E(P14 + 7, N8, S21 + 8);

	smb_E(S21, C8, RN);
	smb_E(S21 + 7, C8, RN + 8);
	smb_E(S21 + 14, C8, RN + 16);
	free(p, M_SMBTEMP);
	return 0;
}