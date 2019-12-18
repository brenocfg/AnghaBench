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
struct socket_info {int fd; int /*<<< orphan*/  io; int /*<<< orphan*/  peername_len; void* peername; int /*<<< orphan*/  myname_len; void* myname; void* tmp_path; void* path; int /*<<< orphan*/  bcast; int /*<<< orphan*/  bound; int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWRAP_DLIST_ADD (int /*<<< orphan*/ ,struct socket_info*) ; 
 scalar_t__ calloc (int,int) ; 
 void* sockaddr_dup (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockets ; 
 void* strdup (void*) ; 

__attribute__((used)) static int
dup_internal(const struct socket_info *si_oldd, int fd)
{
	struct socket_info *si_newd;

	si_newd = (struct socket_info *)calloc(1, sizeof(struct socket_info));

	si_newd->fd = fd;

	si_newd->family = si_oldd->family;
	si_newd->type = si_oldd->type;
	si_newd->protocol = si_oldd->protocol;
	si_newd->bound = si_oldd->bound;
	si_newd->bcast = si_oldd->bcast;
	if (si_oldd->path)
		si_newd->path = strdup(si_oldd->path);
	if (si_oldd->tmp_path)
		si_newd->tmp_path = strdup(si_oldd->tmp_path);
	si_newd->myname =
	    sockaddr_dup(si_oldd->myname, si_oldd->myname_len);
	si_newd->myname_len = si_oldd->myname_len;
	si_newd->peername =
	    sockaddr_dup(si_oldd->peername, si_oldd->peername_len);
	si_newd->peername_len = si_oldd->peername_len;

	si_newd->io = si_oldd->io;

	SWRAP_DLIST_ADD(sockets, si_newd);

	return fd;
}