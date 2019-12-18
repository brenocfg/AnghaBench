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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  BF_LONG ;
typedef  int /*<<< orphan*/  BF_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BF_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
blf_encrypt(caddr_t key, u_int8_t *blk)
{
	BF_LONG t[2];

	memcpy(t, blk, sizeof (t));
	t[0] = ntohl(t[0]);
	t[1] = ntohl(t[1]);
	/* NB: BF_encrypt expects the block in host order! */
	BF_encrypt(t, (BF_KEY *) key);
	t[0] = htonl(t[0]);
	t[1] = htonl(t[1]);
	memcpy(blk, t, sizeof (t));
}