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
 int eDecrypt ; 
 int /*<<< orphan*/  put32 (struct client*,int) ; 
 int /*<<< orphan*/  putdata (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ret32 (struct client*,int) ; 
 int /*<<< orphan*/  retdata (struct client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
decrypt_token(struct client *client, int32_t hContext, int flags,
	     krb5_data *in, krb5_data *out)
{
    int32_t val;
    put32(client, eDecrypt);
    put32(client, hContext);
    put32(client, flags);
    put32(client, 0);
    putdata(client, *in);
    ret32(client, val);
    retdata(client, *out);
    return val;
}