#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct imap_store {TYPE_2__* imap; } ;
struct imap_cmd {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pass; int /*<<< orphan*/  user; } ;
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
struct TYPE_5__ {TYPE_1__ buf; } ;

/* Variables and functions */
 char* cram (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int error (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_3__ server ; 
 int socket_write (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int auth_cram_md5(struct imap_store *ctx, struct imap_cmd *cmd, const char *prompt)
{
	int ret;
	char *response;

	response = cram(prompt, server.user, server.pass);

	ret = socket_write(&ctx->imap->buf.sock, response, strlen(response));
	if (ret != strlen(response))
		return error("IMAP error: sending response failed");

	free(response);

	return 0;
}