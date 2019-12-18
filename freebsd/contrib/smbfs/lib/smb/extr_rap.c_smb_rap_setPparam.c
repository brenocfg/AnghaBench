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
struct smb_rap {char* r_nparam; void* r_rcvbuf; } ;

/* Variables and functions */
 int EINVAL ; 
 int smb_rap_parserqparam (char*,char**,int*) ; 

int
smb_rap_setPparam(struct smb_rap *rap, void *value)
{
	char *p = rap->r_nparam;
	char ptype = *p;
	int error, plen;

	error = smb_rap_parserqparam(p, &p, &plen);
	if (error)
		return error;
	switch (ptype) {
	    case 'r':
		rap->r_rcvbuf = value;
		break;
	    default:
		return EINVAL;
	}
	rap->r_nparam = p;
	return 0;
}