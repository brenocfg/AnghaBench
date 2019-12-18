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
struct client {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int int32_t ;

/* Variables and functions */
 int eAcceptContext ; 
 int /*<<< orphan*/  krb5_data_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put32 (struct client*,int) ; 
 int /*<<< orphan*/  putdata (struct client*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ret32 (struct client*,int) ; 
 int /*<<< orphan*/  retdata (struct client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
accept_sec_context(struct client *client,
		   int32_t *hContext,
		   int32_t flags,
		   const krb5_data *itoken,
		   krb5_data *otoken,
		   int32_t *hDelegCred)
{
    int32_t val;
    krb5_data_zero(otoken);
    put32(client, eAcceptContext);
    put32(client, *hContext);
    put32(client, flags);
    putdata(client, *itoken);
    ret32(client, *hContext);
    ret32(client, val);
    retdata(client, *otoken);
    ret32(client, *hDelegCred);
    return val;
}