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
struct imap_server_conf {char* host; void* pass; void* user; scalar_t__ use_ssl; } ;
struct credential {char* username; char* password; void* host; void* protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  credential_fill (struct credential*) ; 
 void* xstrdup (char*) ; 
 void* xstrdup_or_null (void*) ; 

__attribute__((used)) static void server_fill_credential(struct imap_server_conf *srvc, struct credential *cred)
{
	if (srvc->user && srvc->pass)
		return;

	cred->protocol = xstrdup(srvc->use_ssl ? "imaps" : "imap");
	cred->host = xstrdup(srvc->host);

	cred->username = xstrdup_or_null(srvc->user);
	cred->password = xstrdup_or_null(srvc->pass);

	credential_fill(cred);

	if (!srvc->user)
		srvc->user = xstrdup(cred->username);
	if (!srvc->pass)
		srvc->pass = xstrdup(cred->password);
}