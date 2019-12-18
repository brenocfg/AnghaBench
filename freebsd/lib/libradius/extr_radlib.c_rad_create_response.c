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
struct rad_handle {scalar_t__ type; int* out; int* in; int out_created; scalar_t__ authentic_pos; int /*<<< orphan*/  out_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEN_AUTH ; 
 int /*<<< orphan*/  POS_ATTRS ; 
 size_t POS_AUTH ; 
 size_t POS_CODE ; 
 size_t POS_IDENT ; 
 scalar_t__ RADIUS_SERVER ; 
 int /*<<< orphan*/  clear_password (struct rad_handle*) ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
rad_create_response(struct rad_handle *h, int code)
{

	if (h->type != RADIUS_SERVER) {
		generr(h, "denied function call");
		return (-1);
	}
	h->out[POS_CODE] = code;
	h->out[POS_IDENT] = h->in[POS_IDENT];
	memset(&h->out[POS_AUTH], 0, LEN_AUTH);
	h->out_len = POS_ATTRS;
	clear_password(h);
	h->authentic_pos = 0;
	h->out_created = 1;
	return 0;
}