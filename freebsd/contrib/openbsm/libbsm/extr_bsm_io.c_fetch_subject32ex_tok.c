#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_6__ {scalar_t__ port; scalar_t__ type; int /*<<< orphan*/ * addr; } ;
struct TYPE_7__ {scalar_t__ auid; scalar_t__ euid; scalar_t__ egid; scalar_t__ ruid; scalar_t__ rgid; scalar_t__ pid; scalar_t__ sid; TYPE_1__ tid; } ;
struct TYPE_8__ {TYPE_2__ subj32_ex; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; TYPE_3__ tt; } ;
typedef  TYPE_4__ tokenstr_t ;

/* Variables and functions */
 scalar_t__ AU_IPv4 ; 
 scalar_t__ AU_IPv6 ; 
 int /*<<< orphan*/  READ_TOKEN_BYTES (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  READ_TOKEN_U_INT32 (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fetch_subject32ex_tok(tokenstr_t *tok, u_char *buf, int len)
{
	int err = 0;

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.auid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.euid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.egid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.ruid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.rgid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.pid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.sid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.tid.port, tok->len,
	    err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.subj32_ex.tid.type, tok->len,
	    err);
	if (err)
		return (-1);

	if (tok->tt.subj32_ex.tid.type == AU_IPv4) {
		READ_TOKEN_BYTES(buf, len, &tok->tt.subj32_ex.tid.addr[0],
		    sizeof(tok->tt.subj32_ex.tid.addr[0]), tok->len, err);
		if (err)
			return (-1);
	} else if (tok->tt.subj32_ex.tid.type == AU_IPv6) {
		READ_TOKEN_BYTES(buf, len, tok->tt.subj32_ex.tid.addr,
		    sizeof(tok->tt.subj32_ex.tid.addr), tok->len, err);
		if (err)
			return (-1);
	} else
		return (-1);

	return (0);
}