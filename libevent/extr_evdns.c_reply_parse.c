#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  unsigned int u16 ;
typedef  int /*<<< orphan*/  tmp_name ;
struct request {unsigned int request_type; int request_len; int /*<<< orphan*/ * put_cname_in_ptr; int /*<<< orphan*/ * request; struct evdns_base* base; } ;
struct TYPE_7__ {int addrcount; int /*<<< orphan*/ * addresses; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {int addrcount; int /*<<< orphan*/ * addresses; } ;
struct TYPE_8__ {TYPE_3__ aaaa; TYPE_2__ ptr; TYPE_1__ a; } ;
struct reply {unsigned int type; int have_answer; TYPE_4__ data; } ;
struct evdns_base {int /*<<< orphan*/  global_randomize_case; } ;
typedef  int /*<<< orphan*/  reply ;
typedef  int /*<<< orphan*/  cname ;
typedef  int /*<<< orphan*/  cmp_name ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (struct evdns_base*) ; 
 unsigned int CLASS_INET ; 
 unsigned int DNS_ERR_NOTEXIST ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  GET16 (unsigned int) ; 
 int /*<<< orphan*/  GET32 (int) ; 
 int HOST_NAME_MAX ; 
 int MAX_V4_ADDRS ; 
 int MAX_V6_ADDRS ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  SKIP_NAME ; 
 unsigned int TYPE_A ; 
 unsigned int TYPE_AAAA ; 
 unsigned int TYPE_CNAME ; 
 unsigned int TYPE_PTR ; 
 unsigned int TYPE_SOA ; 
 unsigned int _QR_MASK ; 
 unsigned int _RCODE_MASK ; 
 unsigned int _TC_MASK ; 
 scalar_t__ evutil_ascii_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct reply*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mm_strdup (char*) ; 
 scalar_t__ name_parse (int /*<<< orphan*/ *,int,int*,char*,int) ; 
 int /*<<< orphan*/  reply_handle (struct request*,unsigned int,int,struct reply*) ; 
 struct request* request_find_from_trans_id (struct evdns_base*,unsigned int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
reply_parse(struct evdns_base *base, u8 *packet, int length) {
	int j = 0, k = 0;  /* index into packet */
	u16 t_;	 /* used by the macros */
	u32 t32_;  /* used by the macros */
	char tmp_name[256], cmp_name[256]; /* used by the macros */
	int name_matches = 0;

	u16 trans_id, questions, answers, authority, additional, datalength;
	u16 flags = 0;
	u32 ttl, ttl_r = 0xffffffff;
	struct reply reply;
	struct request *req = NULL;
	unsigned int i;

	ASSERT_LOCKED(base);

	GET16(trans_id);
	GET16(flags);
	GET16(questions);
	GET16(answers);
	GET16(authority);
	GET16(additional);
	(void) authority; /* suppress "unused variable" warnings. */
	(void) additional; /* suppress "unused variable" warnings. */

	req = request_find_from_trans_id(base, trans_id);
	if (!req) return -1;
	EVUTIL_ASSERT(req->base == base);

	memset(&reply, 0, sizeof(reply));

	/* If it's not an answer, it doesn't correspond to any request. */
	if (!(flags & _QR_MASK)) return -1;  /* must be an answer */
	if ((flags & (_RCODE_MASK|_TC_MASK)) && (flags & (_RCODE_MASK|_TC_MASK)) != DNS_ERR_NOTEXIST) {
		/* there was an error and it's not NXDOMAIN */
		goto err;
	}
	/* if (!answers) return; */  /* must have an answer of some form */

	/* This macro skips a name in the DNS reply. */
#define SKIP_NAME						\
	do { tmp_name[0] = '\0';				\
		if (name_parse(packet, length, &j, tmp_name,	\
			sizeof(tmp_name))<0)			\
			goto err;				\
	} while (0)

	reply.type = req->request_type;

	/* skip over each question in the reply */
	for (i = 0; i < questions; ++i) {
		/* the question looks like
		 *   <label:name><u16:type><u16:class>
		 */
		tmp_name[0] = '\0';
		cmp_name[0] = '\0';
		k = j;
		if (name_parse(packet, length, &j, tmp_name, sizeof(tmp_name)) < 0)
			goto err;
		if (name_parse(req->request, req->request_len, &k,
			cmp_name, sizeof(cmp_name))<0)
			goto err;
		if (!base->global_randomize_case) {
			if (strcmp(tmp_name, cmp_name) == 0)
				name_matches = 1;
		} else {
			if (evutil_ascii_strcasecmp(tmp_name, cmp_name) == 0)
				name_matches = 1;
		}

		j += 4;
		if (j > length)
			goto err;
	}

	if (!name_matches)
		goto err;

	/* now we have the answer section which looks like
	 * <label:name><u16:type><u16:class><u32:ttl><u16:len><data...>
	 */

	for (i = 0; i < answers; ++i) {
		u16 type, class;

		SKIP_NAME;
		GET16(type);
		GET16(class);
		GET32(ttl);
		GET16(datalength);

		if (type == TYPE_A && class == CLASS_INET) {
			int addrcount, addrtocopy;
			if (req->request_type != TYPE_A) {
				j += datalength; continue;
			}
			if ((datalength & 3) != 0) /* not an even number of As. */
			    goto err;
			addrcount = datalength >> 2;
			addrtocopy = MIN(MAX_V4_ADDRS - reply.data.a.addrcount, (unsigned)addrcount);

			ttl_r = MIN(ttl_r, ttl);
			/* we only bother with the first four addresses. */
			if (j + 4*addrtocopy > length) goto err;
			memcpy(&reply.data.a.addresses[reply.data.a.addrcount],
				   packet + j, 4*addrtocopy);
			j += 4*addrtocopy;
			reply.data.a.addrcount += addrtocopy;
			reply.have_answer = 1;
			if (reply.data.a.addrcount == MAX_V4_ADDRS) break;
		} else if (type == TYPE_PTR && class == CLASS_INET) {
			if (req->request_type != TYPE_PTR) {
				j += datalength; continue;
			}
			if (name_parse(packet, length, &j, reply.data.ptr.name,
						   sizeof(reply.data.ptr.name))<0)
				goto err;
			ttl_r = MIN(ttl_r, ttl);
			reply.have_answer = 1;
			break;
		} else if (type == TYPE_CNAME) {
			char cname[HOST_NAME_MAX];
			if (!req->put_cname_in_ptr || *req->put_cname_in_ptr) {
				j += datalength; continue;
			}
			if (name_parse(packet, length, &j, cname,
				sizeof(cname))<0)
				goto err;
			*req->put_cname_in_ptr = mm_strdup(cname);
		} else if (type == TYPE_AAAA && class == CLASS_INET) {
			int addrcount, addrtocopy;
			if (req->request_type != TYPE_AAAA) {
				j += datalength; continue;
			}
			if ((datalength & 15) != 0) /* not an even number of AAAAs. */
				goto err;
			addrcount = datalength >> 4;  /* each address is 16 bytes long */
			addrtocopy = MIN(MAX_V6_ADDRS - reply.data.aaaa.addrcount, (unsigned)addrcount);
			ttl_r = MIN(ttl_r, ttl);

			/* we only bother with the first four addresses. */
			if (j + 16*addrtocopy > length) goto err;
			memcpy(&reply.data.aaaa.addresses[reply.data.aaaa.addrcount],
				   packet + j, 16*addrtocopy);
			reply.data.aaaa.addrcount += addrtocopy;
			j += 16*addrtocopy;
			reply.have_answer = 1;
			if (reply.data.aaaa.addrcount == MAX_V6_ADDRS) break;
		} else {
			/* skip over any other type of resource */
			j += datalength;
		}
	}

	if (!reply.have_answer) {
		for (i = 0; i < authority; ++i) {
			u16 type, class;
			SKIP_NAME;
			GET16(type);
			GET16(class);
			GET32(ttl);
			GET16(datalength);
			if (type == TYPE_SOA && class == CLASS_INET) {
				u32 serial, refresh, retry, expire, minimum;
				SKIP_NAME;
				SKIP_NAME;
				GET32(serial);
				GET32(refresh);
				GET32(retry);
				GET32(expire);
				GET32(minimum);
				(void)expire;
				(void)retry;
				(void)refresh;
				(void)serial;
				ttl_r = MIN(ttl_r, ttl);
				ttl_r = MIN(ttl_r, minimum);
			} else {
				/* skip over any other type of resource */
				j += datalength;
			}
		}
	}

	if (ttl_r == 0xffffffff)
		ttl_r = 0;

	reply_handle(req, flags, ttl_r, &reply);
	return 0;
 err:
	if (req)
		reply_handle(req, flags, 0, NULL);
	return -1;
}