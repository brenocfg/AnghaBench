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
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  nid; int /*<<< orphan*/  fsid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_1__ attr32; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ_TOKEN_U_INT32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  READ_TOKEN_U_INT64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fetch_attr32_tok(tokenstr_t *tok, u_char *buf, int len)
{
	int err = 0;

	READ_TOKEN_U_INT32(buf, len, tok->tt.attr32.mode, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.attr32.uid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.attr32.gid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.attr32.fsid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT64(buf, len, tok->tt.attr32.nid, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_INT32(buf, len, tok->tt.attr32.dev, tok->len, err);
	if (err)
		return (-1);

	return (0);
}