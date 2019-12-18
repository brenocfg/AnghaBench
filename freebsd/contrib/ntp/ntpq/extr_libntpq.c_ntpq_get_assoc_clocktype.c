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
typedef  int /*<<< orphan*/  sockaddr_u ;
typedef  int /*<<< orphan*/  resultbuf ;
typedef  int /*<<< orphan*/  dstadr ;
typedef  scalar_t__ associd_t ;
struct TYPE_2__ {scalar_t__ assid; } ;

/* Variables and functions */
 int LENHOSTNAME ; 
 int NTPQ_BUFLEN ; 
 TYPE_1__* assoc_cache ; 
 scalar_t__ decodenetnum (char*,int /*<<< orphan*/ *) ; 
 int ntpq_decodeaddrtype (int /*<<< orphan*/ *) ; 
 int ntpq_get_peervar (char*,char*,int) ; 
 int ntpq_getvar (char*,int,char*,char*,int) ; 
 int ntpq_read_assoc_peervars (scalar_t__,char*,int) ; 
 int numassoc ; 
 scalar_t__ peervar_assoc ; 

int
ntpq_get_assoc_clocktype(
	int assoc_index
	)
{
	associd_t	associd;
	int		i;
	int		rc;
	sockaddr_u	dum_store;
	char		dstadr[LENHOSTNAME];
	char		resultbuf[NTPQ_BUFLEN];

	if (assoc_index < 0 || assoc_index >= numassoc)
		return -1;

	associd = assoc_cache[assoc_index].assid;
	if (associd == peervar_assoc) {
		rc = ntpq_get_peervar("dstadr", dstadr, sizeof(dstadr));
	} else {
		i = ntpq_read_assoc_peervars(associd, resultbuf,
					     sizeof(resultbuf));
		if (i <= 0)
			return -1;
		rc = ntpq_getvar(resultbuf, i, "dstadr", dstadr,
				 sizeof(dstadr));
	}

	if (0 != rc && decodenetnum(dstadr, &dum_store))
		return ntpq_decodeaddrtype(&dum_store);

	return -1;
}