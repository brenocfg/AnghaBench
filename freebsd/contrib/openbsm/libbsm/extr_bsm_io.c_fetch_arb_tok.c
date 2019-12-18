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
struct TYPE_5__ {int howtopr; int bu; int uc; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {TYPE_1__ arb; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; TYPE_2__ tt; } ;
typedef  TYPE_3__ tokenstr_t ;

/* Variables and functions */
#define  AUR_BYTE 131 
 int AUR_BYTE_SIZE ; 
#define  AUR_INT32 130 
 int AUR_INT32_SIZE ; 
#define  AUR_INT64 129 
 int AUR_INT64_SIZE ; 
#define  AUR_SHORT 128 
 int AUR_SHORT_SIZE ; 
 int /*<<< orphan*/  READ_TOKEN_U_CHAR (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_PTR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fetch_arb_tok(tokenstr_t *tok, u_char *buf, int len)
{
	int err = 0;
	int datasize;

	READ_TOKEN_U_CHAR(buf, len, tok->tt.arb.howtopr, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_CHAR(buf, len, tok->tt.arb.bu, tok->len, err);
	if (err)
		return (-1);

	READ_TOKEN_U_CHAR(buf, len, tok->tt.arb.uc, tok->len, err);
	if (err)
		return (-1);

	/*
	 * Determine the size of the basic unit.
	 */
	switch(tok->tt.arb.bu) {
	case AUR_BYTE:
	/* case AUR_CHAR: */
		datasize = AUR_BYTE_SIZE;
		break;

	case AUR_SHORT:
		datasize = AUR_SHORT_SIZE;
		break;

	case AUR_INT32:
	/* case AUR_INT: */
		datasize = AUR_INT32_SIZE;
		break;

	case AUR_INT64:
		datasize = AUR_INT64_SIZE;
		break;

	default:
		return (-1);
	}

	SET_PTR(buf, len, tok->tt.arb.data, datasize * tok->tt.arb.uc,
	    tok->len, err);
	if (err)
		return (-1);

	return (0);
}