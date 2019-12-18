#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct ws_buf {scalar_t__ n; scalar_t__ buf; scalar_t__ base; } ;
struct TYPE_3__ {void* md5_pkt_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  au_pw; TYPE_1__ a_md5; } ;
struct netauth {TYPE_2__ au; void* a_type; int /*<<< orphan*/  a_family; } ;
struct auth {int /*<<< orphan*/ * key; } ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  RIP_AF_AUTH ; 
 scalar_t__ RIP_AUTH_MD5_HASH_XTRA ; 
 scalar_t__ RIP_AUTH_MD5_KEY_LEN ; 
 void* htons (int) ; 

void
end_md5_auth(struct ws_buf *wb,
	     struct auth *ap)
{
	struct netauth *na, *na2;
	MD5_CTX md5_ctx;
	int len;


	na = (struct netauth*)wb->base;
	na2 = (struct netauth*)wb->n;
	len = (char *)na2-(char *)wb->buf;
	na2->a_family = RIP_AF_AUTH;
	na2->a_type = htons(1);
	na->au.a_md5.md5_pkt_len = htons(len);
	MD5Init(&md5_ctx);
	MD5Update(&md5_ctx, (u_char *)wb->buf, len + RIP_AUTH_MD5_HASH_XTRA);
	MD5Update(&md5_ctx, ap->key, RIP_AUTH_MD5_KEY_LEN);
	MD5Final(na2->au.au_pw, &md5_ctx);
	wb->n++;
}