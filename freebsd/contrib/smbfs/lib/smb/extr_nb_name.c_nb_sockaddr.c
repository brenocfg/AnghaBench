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
struct sockaddr_nb {int /*<<< orphan*/  snb_tran; int /*<<< orphan*/  snb_name; } ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct nb_name {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_IPX ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int NB_ENCNAMELEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int nb_name_encode (struct nb_name*,int /*<<< orphan*/ ) ; 
 int nb_name_len (struct nb_name*) ; 
 int nb_snballoc (int,struct sockaddr_nb**) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
nb_sockaddr(struct sockaddr *peer, struct nb_name *np,
	struct sockaddr_nb **dst)

{
	struct sockaddr_nb *snb;
	int nmlen, error;

	if (peer && (peer->sa_family != AF_INET && peer->sa_family != AF_IPX))
		return EPROTONOSUPPORT;
	nmlen = nb_name_len(np);
	if (nmlen < NB_ENCNAMELEN)
		return EINVAL;
	error = nb_snballoc(nmlen, &snb);
	if (error)
		return error;
	if (nmlen != nb_name_encode(np, snb->snb_name))
		printf("a bug somewhere in the nb_name* code\n");
	if (peer)
		memcpy(&snb->snb_tran, peer, peer->sa_len);
	*dst = snb;
	return 0;
}