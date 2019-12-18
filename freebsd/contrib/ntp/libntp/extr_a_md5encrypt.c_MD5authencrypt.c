#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u_int32 ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {int member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ rwbuffT ;
struct TYPE_7__ {size_t member_1; int /*<<< orphan*/  const* member_0; } ;
typedef  TYPE_2__ robuffT ;
typedef  int /*<<< orphan*/  digest ;

/* Variables and functions */
 int EVP_MAX_MD_SIZE ; 
 int KEY_MAC_LEN ; 
 size_t MAX_MDG_LEN ; 
 size_t make_mac (TYPE_1__*,int,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

size_t
MD5authencrypt(
	int		type,	/* hash algorithm */
	const u_char *	key,	/* key pointer */
	size_t		klen,	/* key length */
	u_int32 *	pkt,	/* packet pointer */
	size_t		length	/* packet length */
	)
{
	u_char	digest[EVP_MAX_MD_SIZE];
	rwbuffT digb = { digest, sizeof(digest) };
	robuffT keyb = { key, klen };
	robuffT msgb = { pkt, length };	
	size_t	dlen = 0;

	dlen = make_mac(&digb, type, &keyb, &msgb);
	/* If the MAC is longer than the MAX then truncate it. */
	if (dlen > MAX_MDG_LEN)
		dlen = MAX_MDG_LEN;
	memcpy((u_char *)pkt + length + KEY_MAC_LEN, digest, dlen);
	return (dlen + KEY_MAC_LEN);
}