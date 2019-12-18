#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int /*<<< orphan*/  tstamp; struct autokey* ptr; } ;
struct peer {int flags; int keyid; char const* hostname; int r21; int r34; int throttle; int leap; int hmode; int stratum; int ppoll; int hpoll; int rootdelay; int rootdisp; int xleave; int bias; int reach; int flash; int ttl; int unreach; int nextdate; int delay; int offset; int jitter; int disp; int pmode; int received; int sent; int timereceived; int timereachable; int badauth; int bogusorg; int oldpkt; int seldisptoolarge; int selbroken; int status; int crypto; char const* subject; char const* ident; TYPE_2__ recval; int /*<<< orphan*/  filter_nextpt; int /*<<< orphan*/  filter_disp; int /*<<< orphan*/  filter_offset; int /*<<< orphan*/  filter_delay; int /*<<< orphan*/  dst; int /*<<< orphan*/  aorg; int /*<<< orphan*/  reftime; int /*<<< orphan*/  refid; int /*<<< orphan*/  precision; TYPE_1__* dstadr; int /*<<< orphan*/  srcadr; } ;
struct ctl_var {char const* text; int flags; } ;
struct autokey {int key; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  sin; } ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int COUNTOF (int /*<<< orphan*/ *) ; 
#define  CP_AUTHENABLE 183 
#define  CP_AUTHENTIC 182 
#define  CP_BADAUTH 181 
#define  CP_BIAS 180 
#define  CP_BOGUSORG 179 
#define  CP_CANDIDATE 178 
#define  CP_CONFIG 177 
#define  CP_DELAY 176 
#define  CP_DISPERSION 175 
#define  CP_DSTADR 174 
#define  CP_DSTPORT 173 
#define  CP_FILTDELAY 172 
#define  CP_FILTERROR 171 
#define  CP_FILTOFFSET 170 
#define  CP_FLAGS 169 
#define  CP_FLASH 168 
#define  CP_HMODE 167 
#define  CP_HOST 166 
#define  CP_HPOLL 165 
#define  CP_IDENT 164 
#define  CP_IN 163 
 size_t CP_INITKEY ; 
#define  CP_INITSEQ 162 
 size_t CP_INITTSP ; 
#define  CP_JITTER 161 
#define  CP_KEYID 160 
#define  CP_LEAP 159 
#define  CP_OFFSET 158 
#define  CP_OLDPKT 157 
#define  CP_ORG 156 
#define  CP_OUT 155 
#define  CP_PMODE 154 
#define  CP_PPOLL 153 
#define  CP_PRECISION 152 
#define  CP_RATE 151 
#define  CP_REACH 150 
#define  CP_REC 149 
#define  CP_RECEIVED 148 
#define  CP_REFID 147 
#define  CP_REFTIME 146 
#define  CP_ROOTDELAY 145 
#define  CP_ROOTDISPERSION 144 
#define  CP_SELBROKEN 143 
#define  CP_SELDISP 142 
#define  CP_SENT 141 
#define  CP_SIGNATURE 140 
#define  CP_SRCADR 139 
#define  CP_SRCHOST 138 
#define  CP_SRCPORT 137 
#define  CP_STRATUM 136 
#define  CP_TIMER 135 
#define  CP_TIMEREACH 134 
#define  CP_TIMEREC 133 
#define  CP_TTL 132 
#define  CP_UNREACH 131 
#define  CP_VALID 130 
#define  CP_VARLIST 129 
#define  CP_XMT 128 
 int CTL_MAX_DATA_LEN ; 
 int EOV ; 
 int /*<<< orphan*/  EVP_MD_pkey_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int FLAG_AUTHENTIC ; 
 int FLAG_PREEMPT ; 
 int FLAG_REFCLOCK ; 
 int NTP_MAXKEY ; 
 char* OBJ_nid2ln (int /*<<< orphan*/ ) ; 
 int PADDING ; 
 int /*<<< orphan*/  REFID_ISTEXT (int) ; 
 int SRCPORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_putadr (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_putarray (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putdata (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putdbl (char const*,int) ; 
 int /*<<< orphan*/  ctl_putfs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_puthex (char const*,int) ; 
 int /*<<< orphan*/  ctl_putint (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putrefid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putstr (char const*,char const*,int) ; 
 int /*<<< orphan*/  ctl_putts (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_putuint (char const*,int) ; 
 int current_time ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct ctl_var* peer_var ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/ * sys_ttl ; 

__attribute__((used)) static void
ctl_putpeer(
	int id,
	struct peer *p
	)
{
	char buf[CTL_MAX_DATA_LEN];
	char *s;
	char *t;
	char *be;
	int i;
	const struct ctl_var *k;
#ifdef AUTOKEY
	struct autokey *ap;
	const EVP_MD *dp;
	const char *str;
#endif	/* AUTOKEY */

	switch (id) {

	case CP_CONFIG:
		ctl_putuint(peer_var[id].text,
			    !(FLAG_PREEMPT & p->flags));
		break;

	case CP_AUTHENABLE:
		ctl_putuint(peer_var[id].text, !(p->keyid));
		break;

	case CP_AUTHENTIC:
		ctl_putuint(peer_var[id].text,
			    !!(FLAG_AUTHENTIC & p->flags));
		break;

	case CP_SRCADR:
		ctl_putadr(peer_var[id].text, 0, &p->srcadr);
		break;

	case CP_SRCPORT:
		ctl_putuint(peer_var[id].text, SRCPORT(&p->srcadr));
		break;

	case CP_SRCHOST:
		if (p->hostname != NULL)
			ctl_putstr(peer_var[id].text, p->hostname,
				   strlen(p->hostname));
		break;

	case CP_DSTADR:
		ctl_putadr(peer_var[id].text, 0,
			   (p->dstadr != NULL)
				? &p->dstadr->sin
				: NULL);
		break;

	case CP_DSTPORT:
		ctl_putuint(peer_var[id].text,
			    (p->dstadr != NULL)
				? SRCPORT(&p->dstadr->sin)
				: 0);
		break;

	case CP_IN:
		if (p->r21 > 0.)
			ctl_putdbl(peer_var[id].text, p->r21 / 1e3);
		break;

	case CP_OUT:
		if (p->r34 > 0.)
			ctl_putdbl(peer_var[id].text, p->r34 / 1e3);
		break;

	case CP_RATE:
		ctl_putuint(peer_var[id].text, p->throttle);
		break;

	case CP_LEAP:
		ctl_putuint(peer_var[id].text, p->leap);
		break;

	case CP_HMODE:
		ctl_putuint(peer_var[id].text, p->hmode);
		break;

	case CP_STRATUM:
		ctl_putuint(peer_var[id].text, p->stratum);
		break;

	case CP_PPOLL:
		ctl_putuint(peer_var[id].text, p->ppoll);
		break;

	case CP_HPOLL:
		ctl_putuint(peer_var[id].text, p->hpoll);
		break;

	case CP_PRECISION:
		ctl_putint(peer_var[id].text, p->precision);
		break;

	case CP_ROOTDELAY:
		ctl_putdbl(peer_var[id].text, p->rootdelay * 1e3);
		break;

	case CP_ROOTDISPERSION:
		ctl_putdbl(peer_var[id].text, p->rootdisp * 1e3);
		break;

	case CP_REFID:
#ifdef REFCLOCK
		if (p->flags & FLAG_REFCLOCK) {
			ctl_putrefid(peer_var[id].text, p->refid);
			break;
		}
#endif
		if (REFID_ISTEXT(p->stratum))
			ctl_putrefid(peer_var[id].text, p->refid);
		else
			ctl_putadr(peer_var[id].text, p->refid, NULL);
		break;

	case CP_REFTIME:
		ctl_putts(peer_var[id].text, &p->reftime);
		break;

	case CP_ORG:
		ctl_putts(peer_var[id].text, &p->aorg);
		break;

	case CP_REC:
		ctl_putts(peer_var[id].text, &p->dst);
		break;

	case CP_XMT:
		if (p->xleave)
			ctl_putdbl(peer_var[id].text, p->xleave * 1e3);
		break;

	case CP_BIAS:
		if (p->bias != 0.)
			ctl_putdbl(peer_var[id].text, p->bias * 1e3);
		break;

	case CP_REACH:
		ctl_puthex(peer_var[id].text, p->reach);
		break;

	case CP_FLASH:
		ctl_puthex(peer_var[id].text, p->flash);
		break;

	case CP_TTL:
#ifdef REFCLOCK
		if (p->flags & FLAG_REFCLOCK) {
			ctl_putuint(peer_var[id].text, p->ttl);
			break;
		}
#endif
		if (p->ttl > 0 && p->ttl < COUNTOF(sys_ttl))
			ctl_putint(peer_var[id].text,
				   sys_ttl[p->ttl]);
		break;

	case CP_UNREACH:
		ctl_putuint(peer_var[id].text, p->unreach);
		break;

	case CP_TIMER:
		ctl_putuint(peer_var[id].text,
			    p->nextdate - current_time);
		break;

	case CP_DELAY:
		ctl_putdbl(peer_var[id].text, p->delay * 1e3);
		break;

	case CP_OFFSET:
		ctl_putdbl(peer_var[id].text, p->offset * 1e3);
		break;

	case CP_JITTER:
		ctl_putdbl(peer_var[id].text, p->jitter * 1e3);
		break;

	case CP_DISPERSION:
		ctl_putdbl(peer_var[id].text, p->disp * 1e3);
		break;

	case CP_KEYID:
		if (p->keyid > NTP_MAXKEY)
			ctl_puthex(peer_var[id].text, p->keyid);
		else
			ctl_putuint(peer_var[id].text, p->keyid);
		break;

	case CP_FILTDELAY:
		ctl_putarray(peer_var[id].text, p->filter_delay,
			     p->filter_nextpt);
		break;

	case CP_FILTOFFSET:
		ctl_putarray(peer_var[id].text, p->filter_offset,
			     p->filter_nextpt);
		break;

	case CP_FILTERROR:
		ctl_putarray(peer_var[id].text, p->filter_disp,
			     p->filter_nextpt);
		break;

	case CP_PMODE:
		ctl_putuint(peer_var[id].text, p->pmode);
		break;

	case CP_RECEIVED:
		ctl_putuint(peer_var[id].text, p->received);
		break;

	case CP_SENT:
		ctl_putuint(peer_var[id].text, p->sent);
		break;

	case CP_VARLIST:
		s = buf;
		be = buf + sizeof(buf);
		if (strlen(peer_var[id].text) + 4 > sizeof(buf))
			break;	/* really long var name */

		snprintf(s, sizeof(buf), "%s=\"", peer_var[id].text);
		s += strlen(s);
		t = s;
		for (k = peer_var; !(EOV & k->flags); k++) {
			if (PADDING & k->flags)
				continue;
			i = strlen(k->text);
			if (s + i + 1 >= be)
				break;
			if (s != t)
				*s++ = ',';
			memcpy(s, k->text, i);
			s += i;
		}
		if (s + 2 < be) {
			*s++ = '"';
			*s = '\0';
			ctl_putdata(buf, (u_int)(s - buf), 0);
		}
		break;

	case CP_TIMEREC:
		ctl_putuint(peer_var[id].text,
			    current_time - p->timereceived);
		break;

	case CP_TIMEREACH:
		ctl_putuint(peer_var[id].text,
			    current_time - p->timereachable);
		break;

	case CP_BADAUTH:
		ctl_putuint(peer_var[id].text, p->badauth);
		break;

	case CP_BOGUSORG:
		ctl_putuint(peer_var[id].text, p->bogusorg);
		break;

	case CP_OLDPKT:
		ctl_putuint(peer_var[id].text, p->oldpkt);
		break;

	case CP_SELDISP:
		ctl_putuint(peer_var[id].text, p->seldisptoolarge);
		break;

	case CP_SELBROKEN:
		ctl_putuint(peer_var[id].text, p->selbroken);
		break;

	case CP_CANDIDATE:
		ctl_putuint(peer_var[id].text, p->status);
		break;
#ifdef AUTOKEY
	case CP_FLAGS:
		if (p->crypto)
			ctl_puthex(peer_var[id].text, p->crypto);
		break;

	case CP_SIGNATURE:
		if (p->crypto) {
			dp = EVP_get_digestbynid(p->crypto >> 16);
			str = OBJ_nid2ln(EVP_MD_pkey_type(dp));
			ctl_putstr(peer_var[id].text, str, strlen(str));
		}
		break;

	case CP_HOST:
		if (p->subject != NULL)
			ctl_putstr(peer_var[id].text, p->subject,
			    strlen(p->subject));
		break;

	case CP_VALID:		/* not used */
		break;

	case CP_INITSEQ:
		if (NULL == (ap = p->recval.ptr))
			break;

		ctl_putint(peer_var[CP_INITSEQ].text, ap->seq);
		ctl_puthex(peer_var[CP_INITKEY].text, ap->key);
		ctl_putfs(peer_var[CP_INITTSP].text,
			  ntohl(p->recval.tstamp));
		break;

	case CP_IDENT:
		if (p->ident != NULL)
			ctl_putstr(peer_var[id].text, p->ident,
			    strlen(p->ident));
		break;


#endif	/* AUTOKEY */
	}
}