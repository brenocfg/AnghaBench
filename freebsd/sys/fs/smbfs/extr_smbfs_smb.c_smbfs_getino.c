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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct smbnode {long n_ino; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,char const*,int) ; 
 int smbfs_hash (char const*,int) ; 

__attribute__((used)) static long
smbfs_getino(struct smbnode *dnp, const char *name, int nmlen)
{
#ifdef USE_MD5_HASH
	MD5_CTX md5;
	u_int32_t state[4];
	long ino;
	int i;

	MD5Init(&md5);
	MD5Update(&md5, name, nmlen);
	MD5Final((u_char *)state, &md5);
	for (i = 0, ino = 0; i < 4; i++)
		ino += state[i];
	return dnp->n_ino + ino;
#endif
	u_int32_t ino;

	ino = dnp->n_ino + smbfs_hash(name, nmlen);
	if (ino <= 2)
		ino += 3;
	return ino;
}