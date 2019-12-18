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
struct TYPE_4__ {int s1; int s2; } ;
struct TYPE_3__ {int low; int high; } ;
struct rpc_err {int re_status; TYPE_2__ re_lb; TYPE_1__ re_vers; scalar_t__ re_why; int /*<<< orphan*/  re_errno; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_GETERR (int /*<<< orphan*/ *,struct rpc_err*) ; 
 int CLNT_PERROR_BUFLEN ; 
#define  RPC_AUTHERROR 145 
#define  RPC_CANTDECODEARGS 144 
#define  RPC_CANTDECODERES 143 
#define  RPC_CANTENCODEARGS 142 
#define  RPC_CANTRECV 141 
#define  RPC_CANTSEND 140 
#define  RPC_FAILED 139 
#define  RPC_PMAPFAILURE 138 
#define  RPC_PROCUNAVAIL 137 
#define  RPC_PROGNOTREGISTERED 136 
#define  RPC_PROGUNAVAIL 135 
#define  RPC_PROGVERSMISMATCH 134 
#define  RPC_SUCCESS 133 
#define  RPC_SYSTEMERROR 132 
#define  RPC_TIMEDOUT 131 
#define  RPC_UNKNOWNHOST 130 
#define  RPC_UNKNOWNPROTO 129 
#define  RPC_VERSMISMATCH 128 
 char* _buf () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* auth_errmsg (scalar_t__) ; 
 int /*<<< orphan*/  clnt_sperrno (int) ; 
 size_t snprintf (char*,size_t,char*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

char *
clnt_sperror(CLIENT *rpch, const char *s)
{
	struct rpc_err e;
	char *err;
	char *str;
	char *strstart;
	size_t len, i;

	assert(rpch != NULL);
	assert(s != NULL);

	str = _buf(); /* side effect: sets CLNT_PERROR_BUFLEN */
	if (str == NULL)
		return (0);
	len = CLNT_PERROR_BUFLEN;
	strstart = str;
	CLNT_GETERR(rpch, &e);

	if ((i = snprintf(str, len, "%s: ", s)) > 0) {
		str += i;
		len -= i;
	}

	(void)strncpy(str, clnt_sperrno(e.re_status), len - 1);
	i = strlen(str);
	str += i;
	len -= i;

	switch (e.re_status) {
	case RPC_SUCCESS:
	case RPC_CANTENCODEARGS:
	case RPC_CANTDECODERES:
	case RPC_TIMEDOUT:
	case RPC_PROGUNAVAIL:
	case RPC_PROCUNAVAIL:
	case RPC_CANTDECODEARGS:
	case RPC_SYSTEMERROR:
	case RPC_UNKNOWNHOST:
	case RPC_UNKNOWNPROTO:
	case RPC_PMAPFAILURE:
	case RPC_PROGNOTREGISTERED:
	case RPC_FAILED:
		break;

	case RPC_CANTSEND:
	case RPC_CANTRECV:
		i = snprintf(str, len, "; errno = %s", strerror(e.re_errno)); 
		if (i > 0) {
			str += i;
			len -= i;
		}
		break;

	case RPC_VERSMISMATCH:
		i = snprintf(str, len, "; low version = %u, high version = %u", 
			e.re_vers.low, e.re_vers.high);
		if (i > 0) {
			str += i;
			len -= i;
		}
		break;

	case RPC_AUTHERROR:
		err = auth_errmsg(e.re_why);
		i = snprintf(str, len, "; why = ");
		if (i > 0) {
			str += i;
			len -= i;
		}
		if (err != NULL) {
			i = snprintf(str, len, "%s",err);
		} else {
			i = snprintf(str, len,
				"(unknown authentication error - %d)",
				(int) e.re_why);
		}
		if (i > 0) {
			str += i;
			len -= i;
		}
		break;

	case RPC_PROGVERSMISMATCH:
		i = snprintf(str, len, "; low version = %u, high version = %u", 
			e.re_vers.low, e.re_vers.high);
		if (i > 0) {
			str += i;
			len -= i;
		}
		break;

	default:	/* unknown */
		i = snprintf(str, len, "; s1 = %u, s2 = %u", 
			e.re_lb.s1, e.re_lb.s2);
		if (i > 0) {
			str += i;
			len -= i;
		}
		break;
	}
	strstart[CLNT_PERROR_BUFLEN-1] = '\0';
	return(strstart) ;
}