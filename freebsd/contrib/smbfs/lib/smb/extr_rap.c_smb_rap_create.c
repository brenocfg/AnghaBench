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
struct smb_rap {char* r_sparam; char* r_nparam; char* r_sdata; char* r_ndata; void* r_npbuf; void* r_pbuf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  bzero (struct smb_rap*,int) ; 
 void* malloc (int) ; 
 scalar_t__ smb_rap_parserqparam (char*,char**,int*) ; 
 int /*<<< orphan*/  smb_rap_rqparam (struct smb_rap*,char,int,int) ; 
 int /*<<< orphan*/  smb_rap_rqparam_z (struct smb_rap*,char*) ; 
 void* strdup (char const*) ; 
 int strlen (char const*) ; 

int
smb_rap_create(int fn, const char *param, const char *data,
	struct smb_rap **rapp)
{
	struct smb_rap *rap;
	char *p;
	int plen, len;

	rap = malloc(sizeof(*rap));
	if (rap == NULL)
		return ENOMEM;
	bzero(rap, sizeof(*rap));
	p = rap->r_sparam = rap->r_nparam = strdup(param);
	rap->r_sdata = rap->r_ndata = strdup(data);
	/*
	 * Calculate length of request parameter block
	 */
	len = 2 + strlen(param) + 1 + strlen(data) + 1;
	
	while (*p) {
		if (smb_rap_parserqparam(p, &p, &plen) != 0)
			break;
		len += plen;
	}
	rap->r_pbuf = rap->r_npbuf = malloc(len);
	smb_rap_rqparam(rap, 'W', 1, fn);
	smb_rap_rqparam_z(rap, rap->r_sparam);
	smb_rap_rqparam_z(rap, rap->r_sdata);
	*rapp = rap;
	return 0;
}