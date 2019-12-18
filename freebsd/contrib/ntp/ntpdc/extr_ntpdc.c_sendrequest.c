#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  void* u_char ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct req_pkt {void* auth_seq; void* mbz_itemsize; void* err_nitems; TYPE_1__ u; void* request; void* implementation; int /*<<< orphan*/  rm_vn_mode; } ;
typedef  int /*<<< orphan*/  l_fp ;
typedef  int /*<<< orphan*/  keyid_t ;

/* Variables and functions */
 void* AUTH_SEQ (int,int /*<<< orphan*/ ) ; 
 void* ERR_NITEMS (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HTONL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L_ADD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* MBZ_ITEMSIZE (size_t) ; 
 size_t REQ_LEN_HDR ; 
 size_t REQ_LEN_NOMAC ; 
 int /*<<< orphan*/  RM_VN_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZERO (struct req_pkt) ; 
 size_t authencrypt (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authistrusted (scalar_t__) ; 
 int /*<<< orphan*/  authtrust (scalar_t__,int) ; 
 int /*<<< orphan*/  authusekey (scalar_t__,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  delay_time ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_systime (int /*<<< orphan*/ *) ; 
 scalar_t__ getkeyid (char*) ; 
 char* getpass_keytype (int /*<<< orphan*/ ) ; 
 int info_auth_hashlen ; 
 scalar_t__ info_auth_keyid ; 
 int /*<<< orphan*/  info_auth_keytype ; 
 scalar_t__ keyid_entered ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t req_pkt_size ; 
 int sendpkt (struct req_pkt*,size_t) ; 
 int /*<<< orphan*/  size2int_chk (size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
sendrequest(
	int implcode,
	int reqcode,
	int auth,
	size_t qitems,
	size_t qsize,
	const char *qdata
	)
{
	struct req_pkt qpkt;
	size_t	datasize;
	size_t	reqsize;
	u_long	key_id;
	l_fp	ts;
	l_fp *	ptstamp;
	size_t	maclen;
	char *	pass;

	ZERO(qpkt);
	qpkt.rm_vn_mode = RM_VN_MODE(0, 0, 0);
	qpkt.implementation = (u_char)implcode;
	qpkt.request = (u_char)reqcode;

	datasize = qitems * qsize;
	if (datasize && qdata != NULL) {
		memcpy(qpkt.u.data, qdata, datasize);
		qpkt.err_nitems = ERR_NITEMS(0, qitems);
		qpkt.mbz_itemsize = MBZ_ITEMSIZE(qsize);
	} else {
		qpkt.err_nitems = ERR_NITEMS(0, 0);
		qpkt.mbz_itemsize = MBZ_ITEMSIZE(qsize);  /* allow for optional first item */
	}

	if (!auth || (keyid_entered && info_auth_keyid == 0)) {
		qpkt.auth_seq = AUTH_SEQ(0, 0);
		return sendpkt(&qpkt, req_pkt_size);
	}

	if (info_auth_keyid == 0) {
		key_id = getkeyid("Keyid: ");
		if (!key_id) {
			fprintf(stderr, "Invalid key identifier\n");
			return 1;
		}
		info_auth_keyid = key_id;
	}
	if (!authistrusted(info_auth_keyid)) {
		pass = getpass_keytype(info_auth_keytype);
		if ('\0' == pass[0]) {
			fprintf(stderr, "Invalid password\n");
			return 1;
		}
		authusekey(info_auth_keyid, info_auth_keytype,
			   (u_char *)pass);
		authtrust(info_auth_keyid, 1);
	}
	qpkt.auth_seq = AUTH_SEQ(1, 0);
	if (info_auth_hashlen > 16) {
		/*
		 * Only ntpd which expects REQ_LEN_NOMAC plus maclen
		 * octets in an authenticated request using a 16 octet
		 * digest (that is, a newer ntpd) will handle digests
		 * larger than 16 octets, so for longer digests, do
		 * not attempt to shorten the requests for downlevel
		 * ntpd compatibility.
		 */
		if (REQ_LEN_NOMAC != req_pkt_size)
			return 1;
		reqsize = REQ_LEN_HDR + datasize + sizeof(*ptstamp);
		/* align to 32 bits */
		reqsize = (reqsize + 3) & ~3;
	} else
		reqsize = req_pkt_size;
	ptstamp = (void *)((char *)&qpkt + reqsize);
	ptstamp--;
	get_systime(&ts);
	L_ADD(&ts, &delay_time);
	HTONL_FP(&ts, ptstamp);
	maclen = authencrypt(
		info_auth_keyid, (void *)&qpkt, size2int_chk(reqsize));
	if (!maclen) {  
		fprintf(stderr, "Key not found\n");
		return 1;
	} else if (maclen != (size_t)(info_auth_hashlen + sizeof(keyid_t))) {
		fprintf(stderr,
			"%zu octet MAC, %zu expected with %zu octet digest\n",
			maclen, (info_auth_hashlen + sizeof(keyid_t)),
			info_auth_hashlen);
		return 1;
	}
	return sendpkt(&qpkt, reqsize + maclen);
}