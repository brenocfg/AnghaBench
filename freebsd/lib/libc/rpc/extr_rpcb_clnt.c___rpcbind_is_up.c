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
struct sockaddr_un {int /*<<< orphan*/  sun_len; int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct netconfig {int /*<<< orphan*/ * nc_protofmly; } ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NC_LOOPBACK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SUN_LEN (struct sockaddr_un*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _PATH_RPCBINDSOCK ; 
 int /*<<< orphan*/  _close (int) ; 
 scalar_t__ _connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int _socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endnetconfig (void*) ; 
 struct netconfig* getnetconfig (void*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 void* setnetconfig () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool_t
__rpcbind_is_up(void)
{
	struct netconfig *nconf;
	struct sockaddr_un sun;
	void *localhandle;
	int sock;

	nconf = NULL;
	localhandle = setnetconfig();
	while ((nconf = getnetconfig(localhandle)) != NULL) {
		if (nconf->nc_protofmly != NULL &&
		    strcmp(nconf->nc_protofmly, NC_LOOPBACK) == 0)
			 break;
	}
	endnetconfig(localhandle);

	if (nconf == NULL)
		return (FALSE);

	memset(&sun, 0, sizeof sun);
	sock = _socket(AF_LOCAL, SOCK_STREAM, 0);
	if (sock < 0)
		return (FALSE);
	sun.sun_family = AF_LOCAL;
	strncpy(sun.sun_path, _PATH_RPCBINDSOCK, sizeof(sun.sun_path));
	sun.sun_len = SUN_LEN(&sun);

	if (_connect(sock, (struct sockaddr *)&sun, sun.sun_len) < 0) {
		_close(sock);
		return (FALSE);
	}

	_close(sock);
	return (TRUE);
}