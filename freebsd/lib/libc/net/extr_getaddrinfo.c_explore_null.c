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
struct afd {int /*<<< orphan*/  a_loopback; int /*<<< orphan*/  a_addrany; } ;
struct addrinfo {scalar_t__ ai_family; int ai_flags; } ;

/* Variables and functions */
 int AI_PASSIVE ; 
 scalar_t__ EMFILE ; 
 int /*<<< orphan*/  GET_AI (struct addrinfo*,struct afd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PORT (struct addrinfo*,char const*) ; 
 scalar_t__ PF_LOCAL ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  _close (int) ; 
 int _socket (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 struct afd* find_afd (scalar_t__) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 

__attribute__((used)) static int
explore_null(const struct addrinfo *pai, const char *servname,
    struct addrinfo **res)
{
	int s;
	const struct afd *afd;
	struct addrinfo *ai;
	int error;

	*res = NULL;
	ai = NULL;

	if (pai->ai_family == PF_LOCAL)
		return (0);

	/*
	 * filter out AFs that are not supported by the kernel
	 * XXX errno?
	 */
	s = _socket(pai->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (s < 0) {
		if (errno != EMFILE)
			return 0;
	} else
		_close(s);

	afd = find_afd(pai->ai_family);
	if (afd == NULL)
		return 0;

	if (pai->ai_flags & AI_PASSIVE) {
		GET_AI(ai, afd, afd->a_addrany);
		GET_PORT(ai, servname);
	} else {
		GET_AI(ai, afd, afd->a_loopback);
		GET_PORT(ai, servname);
	}

	*res = ai;
	return 0;

free:
	if (ai != NULL)
		freeaddrinfo(ai);
	return error;
}