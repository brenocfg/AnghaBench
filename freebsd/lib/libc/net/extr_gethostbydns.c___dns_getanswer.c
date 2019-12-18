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
struct hostent_data {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addrtype; } ;
typedef  int /*<<< orphan*/  res_state ;
typedef  int /*<<< orphan*/  querybuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  NETDB_INTERNAL ; 
 int /*<<< orphan*/  NS_IN6ADDRSZ ; 
 int /*<<< orphan*/  NS_INADDRSZ ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  T_A 129 
#define  T_AAAA 128 
 struct hostent_data* __hostent_data_init () ; 
 struct hostent* __hostent_init () ; 
 int /*<<< orphan*/  __res_state () ; 
 int gethostanswer (int /*<<< orphan*/  const*,int,char const*,int,struct hostent*,struct hostent_data*,int /*<<< orphan*/ ) ; 

struct hostent *
__dns_getanswer(const char *answer, int anslen, const char *qname, int qtype)
{
	struct hostent *he;
	struct hostent_data *hed;
	int error;
	res_state statp;

	statp = __res_state();
	if ((he = __hostent_init()) == NULL ||
	    (hed = __hostent_data_init()) == NULL) {
		RES_SET_H_ERRNO(statp, NETDB_INTERNAL);
		return (NULL);
	}
	switch (qtype) {
	case T_AAAA:
		he->h_addrtype = AF_INET6;
		he->h_length = NS_IN6ADDRSZ;
		break;
	case T_A:
	default:
		he->h_addrtype = AF_INET;
		he->h_length = NS_INADDRSZ;
		break;
	}

	error = gethostanswer((const querybuf *)answer, anslen, qname, qtype,
	    he, hed, statp);
	return (error == 0) ? he : NULL;
}