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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  eWrapExt ; 
 int /*<<< orphan*/  put32 (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putdata (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ret32 (struct client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retdata (struct client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
wrap_token_ext(struct client *client, int32_t hContext, int32_t flags,
	       int32_t bflags, krb5_data *header, krb5_data *in, krb5_data *trailer,
	       krb5_data *out)
{
    int32_t val;
    put32(client, eWrapExt);
    put32(client, hContext);
    put32(client, flags);
    put32(client, bflags);
    putdata(client, *header);
    putdata(client, *in);
    putdata(client, *trailer);
    ret32(client, val);
    retdata(client, *out);
    return val;
}