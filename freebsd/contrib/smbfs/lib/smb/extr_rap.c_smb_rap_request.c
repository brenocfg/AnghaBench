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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct smb_rap {char* r_nparam; int r_rcvbuflen; int r_plen; char* r_rcvbuf; char* r_npbuf; int r_entries; char* r_sdata; void* r_result; scalar_t__ r_pbuf; } ;
struct smb_ctx {int dummy; } ;

/* Variables and functions */
 int EBADRPC ; 
 void* le16toh (int) ; 
 int /*<<< orphan*/  smb_error (char*,int /*<<< orphan*/ ,char*) ; 
 int smb_rap_parserpdata (char*,char**,int*) ; 
 int smb_t2_request (struct smb_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,scalar_t__,int*,char*) ; 

int
smb_rap_request(struct smb_rap *rap, struct smb_ctx *ctx)
{
	u_int16_t *rp, conv;
	u_int32_t *p32;
	char *dp, *p = rap->r_nparam;
	char ptype;
	int error, rdatacnt, rparamcnt, entries, done, dlen;

	rdatacnt = rap->r_rcvbuflen;
	rparamcnt = rap->r_plen;
	error = smb_t2_request(ctx, 0, 0, "\\PIPE\\LANMAN",
	    rap->r_plen, rap->r_pbuf,		/* int tparamcnt, void *tparam */
	    0, NULL,				/* int tdatacnt, void *tdata */
	    &rparamcnt, rap->r_pbuf,		/* rparamcnt, void *rparam */
	    &rdatacnt, rap->r_rcvbuf		/* int *rdatacnt, void *rdata */
	);
	if (error)
		return error;
	rp = (u_int16_t*)rap->r_pbuf;
	rap->r_result = le16toh(*rp++);
	conv = le16toh(*rp++);
	rap->r_npbuf = (char*)rp;
	rap->r_entries = entries = 0;
	done = 0;
	while (!done && *p) {
		ptype = *p;
		switch (ptype) {
		    case 'e':
			rap->r_entries = entries = le16toh(*(u_int16_t*)rap->r_npbuf);
			rap->r_npbuf += 2;
			p++;
			break;
		    default:
			done = 1;
		}
/*		error = smb_rap_parserpparam(p, &p, &plen);
		if (error) {
			smb_error("reply parameter mismath %s", 0, p);
			return EBADRPC;
		}*/
	}
	rap->r_nparam = p;
	/*
	 * In general, unpacking entries we may need to relocate
	 * entries for proper alingning. For now use them as is.
	 */
	dp = rap->r_rcvbuf;
	while (entries--) {
		p = rap->r_sdata;
		while (*p) {
			ptype = *p;
			error = smb_rap_parserpdata(p, &p, &dlen);
			if (error) {
				smb_error("reply data mismath %s", 0, p);
				return EBADRPC;
			}
			switch (ptype) {
			    case 'z':
				p32 = (u_int32_t*)dp;
				*p32 = (*p32 & 0xffff) - conv;
				break;
			}
			dp += dlen;
		}
	}
	return error;
}