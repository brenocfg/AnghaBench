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
struct tlsv1_credentials {int dummy; } ;
struct tlsv1_client {struct tlsv1_credentials* cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  tlsv1_cred_free (struct tlsv1_credentials*) ; 

int tlsv1_client_set_cred(struct tlsv1_client *conn,
			  struct tlsv1_credentials *cred)
{
	tlsv1_cred_free(conn->cred);
	conn->cred = cred;
	return 0;
}