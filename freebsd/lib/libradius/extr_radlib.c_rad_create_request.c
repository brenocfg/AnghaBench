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
typedef  void* u_char ;
struct rad_handle {scalar_t__ type; scalar_t__ num_servers; int* out; int ident; int out_created; scalar_t__ authentic_pos; int /*<<< orphan*/  out_len; } ;

/* Variables and functions */
 int LEN_AUTH ; 
 int /*<<< orphan*/  POS_ATTRS ; 
 int POS_AUTH ; 
 size_t POS_CODE ; 
 size_t POS_IDENT ; 
 scalar_t__ RADIUS_SERVER ; 
 int RAD_ACCESS_REQUEST ; 
 int /*<<< orphan*/  clear_password (struct rad_handle*) ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 long random () ; 

int
rad_create_request(struct rad_handle *h, int code)
{
	int i;

	if (h->type == RADIUS_SERVER) {
		generr(h, "denied function call");
		return (-1);
	}
	if (h->num_servers == 0) {
	    	generr(h, "No RADIUS servers specified");
		return (-1);
	}
	h->out[POS_CODE] = code;
	h->out[POS_IDENT] = ++h->ident;
	if (code == RAD_ACCESS_REQUEST) {
		/* Create a random authenticator */
		for (i = 0;  i < LEN_AUTH;  i += 2) {
			long r;
			r = random();
			h->out[POS_AUTH+i] = (u_char)r;
			h->out[POS_AUTH+i+1] = (u_char)(r >> 8);
		}
	} else
		memset(&h->out[POS_AUTH], 0, LEN_AUTH);
	h->out_len = POS_ATTRS;
	clear_password(h);
	h->authentic_pos = 0;
	h->out_created = 1;
	return 0;
}