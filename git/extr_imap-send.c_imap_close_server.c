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
struct imap_store {struct imap* imap; } ;
struct TYPE_4__ {int* fd; } ;
struct TYPE_3__ {TYPE_2__ sock; } ;
struct imap {TYPE_1__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct imap*) ; 
 int /*<<< orphan*/  imap_exec (struct imap_store*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  socket_shutdown (TYPE_2__*) ; 

__attribute__((used)) static void imap_close_server(struct imap_store *ictx)
{
	struct imap *imap = ictx->imap;

	if (imap->buf.sock.fd[0] != -1) {
		imap_exec(ictx, NULL, "LOGOUT");
		socket_shutdown(&imap->buf.sock);
	}
	free(imap);
}