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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  port; int /*<<< orphan*/  family; } ;
struct TYPE_6__ {TYPE_1__ sockinet_ex32; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_TOKEN_BYTES (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  READ_TOKEN_U_INT16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fetch_sock_inet128_tok(tokenstr_t *tok, u_char *buf, int len)
{
	int err = 0;

	READ_TOKEN_U_INT16(buf, len, tok->tt.sockinet_ex32.family, tok->len,
	    err);
	if (err)
		return (-1);

	READ_TOKEN_BYTES(buf, len, &tok->tt.sockinet_ex32.port,
	    sizeof(uint16_t), tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_BYTES(buf, len, &tok->tt.sockinet_ex32.addr,
	    sizeof(tok->tt.sockinet_ex32.addr), tok->len, err);
	if (err)
		return (-1);

	return (0);
}