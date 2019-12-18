#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  family; } ;
struct TYPE_6__ {TYPE_1__ sockunix; } ;
struct TYPE_7__ {int len; TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_TOKEN_BYTES (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  READ_TOKEN_U_INT16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ memchr (void const*,char,int) ; 

__attribute__((used)) static int
fetch_sock_unix_tok(tokenstr_t *tok, u_char *buf, int len)
{
	int err = 0;
	u_char *p;
	int slen;


	READ_TOKEN_U_INT16(buf, len, tok->tt.sockunix.family, tok->len, err);
	if (err)
		return (-1);

	/* slen = strnlen((buf + tok->len), 104) + 1; */
	p = (u_char *)memchr((const void *)(buf + tok->len), '\0', 104);
	slen = (p ? (int)(p - (buf + tok->len))  : 104) + 1;

	READ_TOKEN_BYTES(buf, len, tok->tt.sockunix.path, slen, tok->len, err);
	if (err)
		return (-1);

	return (0);
}