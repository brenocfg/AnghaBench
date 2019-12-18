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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  keyInstance ;
typedef  int /*<<< orphan*/  cipherInstance ;

/* Variables and functions */
 int /*<<< orphan*/  AES_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AES_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AES_makekey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIR_DECRYPT ; 
 int /*<<< orphan*/  G_BDE_KKEYBITS ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le64dec (int /*<<< orphan*/ *) ; 

int
g_bde_keyloc_decrypt(u_char *sha2, void *input, uint64_t *output)
{
	keyInstance ki;
	cipherInstance ci;
	u_char buf[16];

	AES_init(&ci);
	AES_makekey(&ki, DIR_DECRYPT, G_BDE_KKEYBITS, sha2 + 0);
	AES_decrypt(&ci, &ki, input, buf, sizeof buf);
	*output = le64dec(buf);
	bzero(buf, sizeof buf);
	bzero(&ci, sizeof ci);
	bzero(&ki, sizeof ki);
	return(0);
}