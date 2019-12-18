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
typedef  char u_char ;
struct g_bde_key {int /*<<< orphan*/  mkey; int /*<<< orphan*/  salt; int /*<<< orphan*/  spare; int /*<<< orphan*/ * lsector; int /*<<< orphan*/  flags; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  keyoffset; int /*<<< orphan*/  sectorN; int /*<<< orphan*/  sector0; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int G_BDE_LOCKSIZE ; 
 int /*<<< orphan*/  MD5Final (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,char*,int) ; 
 int NLOCK_FIELDS ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  g_bde_shuffle_lock (char*,int*) ; 
 int /*<<< orphan*/  le32enc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64enc (char*,int /*<<< orphan*/ ) ; 

int
g_bde_encode_lock(u_char *sha2, struct g_bde_key *gl, u_char *ptr)
{
	int shuffle[NLOCK_FIELDS];
	u_char *hash, *p;
	int i;
	MD5_CTX c;

	p = ptr;
	hash = NULL;
	g_bde_shuffle_lock(sha2, shuffle);
	for (i = 0; i < NLOCK_FIELDS; i++) {
		switch(shuffle[i]) {
		case 0:
			le64enc(p, gl->sector0);
			p += 8;
			break;
		case 1:
			le64enc(p, gl->sectorN);
			p += 8;
			break;
		case 2:
			le64enc(p, gl->keyoffset);
			p += 8;
			break;
		case 3:
			le32enc(p, gl->sectorsize);
			p += 4;
			break;
		case 4:
			le32enc(p, gl->flags);
			p += 4;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			le64enc(p, gl->lsector[shuffle[i] - 5]);
			p += 8;
			break;
		case 9:
			bcopy(gl->spare, p, sizeof gl->spare);
			p += sizeof gl->spare;
			break;
		case 10:
			bcopy(gl->salt, p, sizeof gl->salt);
			p += sizeof gl->salt;
			break;
		case 11:
			bcopy(gl->mkey, p, sizeof gl->mkey);
			p += sizeof gl->mkey;
			break;
		case 12:
			bzero(p, 16);
			hash = p;
			p += 16;
			break;
		}
	}
	if(ptr + G_BDE_LOCKSIZE != p)
		return(-1);
	if (hash == NULL)
		return(-1);
	MD5Init(&c);
	MD5Update(&c, "0000", 4);	/* Versioning */
	MD5Update(&c, ptr, G_BDE_LOCKSIZE);
	MD5Final(hash, &c);
	return(0);
}